#include "GraphWriter.h"
#include "boost/process.hpp"
#include "boost/process/windows.hpp"
#include "Config.h"
#include <iostream>
USING_STD using std::deque;
namespace bp  = boost::process;// I didn't use _popen, as that pops up the Cmd window 
namespace fs  = boost::filesystem;

CGraphWriter::CGraphWriter(CGraph& pGraph):m_pGraph(pGraph)
{
}

fs::path CGraphWriter::WriteDOT()
{ //uses BFS 
    fs::path fpDot = fs::current_path() / fs::path("Graphdot.gz");
	std::ofstream fDot(fpDot.string());
	fDot << "graph { \n";
	
	deque<Node*> Q;
	Q.push_back(m_pGraph.GetNodeAt(*m_pGraph.GetNodeIndices().begin()));

	Q.back()->Flag = true; //Visited flag
	while (!Q.empty())
	{
		Node* N = Q.back(); Q.pop_back();
		for (auto It : N->Connections)
		{
			if (!It->Flag)
			{
				fDot << std::to_string(N->index) << " -- " << std::to_string(It->index) << "\n";
				Q.push_back(It.get());
			}
		}

		N->Flag = true;
		Q.pop_back();
	} 

	fDot << "}";
	return fpDot;
}

void CGraphWriter::Visualize(GraphOutType Type)
{
	try 
	{
		fs::path fpDot = WriteDOT();
		bp::system(bp::exe = "dot", bp::args = { "-Tpng Graphdot.gz", "-o Out.png" }); //for this to work, dot has to be added to path variable!
	}
	catch (std::exception& ex) { std::cout << "CGraphWriter::Visualize " << ex.what(); }
}
