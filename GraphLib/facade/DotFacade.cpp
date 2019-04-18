#include "DotFacade.h"
#include <deque>
#include "../Config.h"
#include "boost/process.hpp"
#include "boost/process/windows.hpp"
namespace fs = boost::filesystem;
namespace bp = boost::process;// I didn't use _popen, as that pops up the Cmd window 
USING_STD using std::deque; using std::exception;

CDotFacade::CDotFacade():m_Plot(CConfig::GetInstance()->GetDotPath(), bp::std_in = m_Write, bp::windows::hide)
{
	if (!m_Plot.valid())   { throw exception("Could not load dot.exe");  }
	if (!m_Plot.running()) { throw exception("Could not start dot.exe"); }
}

fs::path CDotFacade::WriteDot(CGraph& pGraph)
{
	fs::path fpDot = fs::current_path() / fs::path("Graphdot.gz");
	std::ofstream fDot(fpDot.string());
	fDot << "graph { \n";

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

	string sCmd = "-T" + sOutType + " -oOut." + sOutType + " " + fpDotfile.string();
	m_Write << sCmd;
	m_Write << "\n";
	return fpDotfile;
}

CDotFacade::~CDotFacade()
{
	m_Write.flush();
	m_Write.pipe().close();

	m_Plot.wait();
	int ret = m_Plot.exit_code();
}
