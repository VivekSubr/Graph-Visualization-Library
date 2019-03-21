#include "GraphWriter.h"
namespace fs = boost::filesystem;
USING_STD
using std::deque;

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

void CGraphWriter::Visualize()
{
    WriteDOT();

//	bp::opstream  m_Write;
//	bp::child     m_Plot;
}
