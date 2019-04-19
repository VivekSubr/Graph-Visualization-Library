#include "DotFacade.h"
#include <deque>
#include "../Config.h"
#include "boost/process.hpp"
namespace fs = boost::filesystem;
namespace bp = boost::process;// I didn't use _popen, as that pops up the Cmd window 
USING_STD using std::deque; using std::exception;

fs::path CDotFacade::WriteDot(CGraph& pGraph)
{
	fs::path fpDot = fs::current_path() / fs::path("Graphdot.gz");
	std::ofstream fDot(fpDot.string());

	if      (pGraph.GetType() == GraphType::UnDirected)  fDot << "graph { \n";
	else if (pGraph.GetType() == GraphType::Directed)    fDot << "digraph { \n";
	else throw exception("unknown type");

	deque<Node*> Q;
	Q.push_back(pGraph.GetNodeAt(*pGraph.GetNodeIndices().begin()));

	Q.back()->Flag = true; //Visited flag
	while (!Q.empty()) //Do BFS on graph
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
	pGraph.ResetFlags();
	return fpDot;
}

fs::path CDotFacade::CreateImage(CGraph& pGraph, ImageType Type)
{
	fs::path fpDotfile = WriteDot(pGraph);
	string sOutType;
	switch (Type)
	{
	   case ImageType::JPG: sOutType = "jpg"; break;
	   default: throw exception("Unknown Type");
	}

	bp::system(CConfig::GetInstance()->GetDotPath(), "-T" + sOutType, "-O", fpDotfile.string(), bp::std_out > "dot.log");
	return fs::path(fpDotfile.string() + "." + sOutType);
}

