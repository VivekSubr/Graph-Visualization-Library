#include "GraphAlgo.h"
#include <cassert>
#include <deque>
#include <queue>
#include <functional>
using std::string; using std::deque; using std::runtime_error; using std::map; using std::vector;

CGraphAlgo::CGraphAlgo(CGraph* pGraph): m_pGraph(nullptr)
{
	m_pGraph = pGraph;
}

bool CGraphAlgo::BFS(int iRoot, int iNode)
{
	deque<Node*> Q;
	Q.push_back(m_pGraph->GetNodeAt(iRoot));

	Q.back()->Flag = true; //Visited flag
	while (!Q.empty())
	{
		Node* N = Q.back(); Q.pop_back();
		for (auto It : N->Connections)
		{
			if (!It->Flag) Q.push_back(It.get());
		}

		if (N->index == iNode) return true;

		N->Flag = true;
		Q.pop_back();
	} return false;
}

bool CGraphAlgo::DFS(int iRoot, int iNode)
{
	Node *N = m_pGraph->GetNodeAt(iRoot);
	N->Flag = true;
	for (auto It : N->Connections)
	{
		if (It->index == iNode) return true;
		if (!It->Flag) DFS(It->Flag, iNode);
	} return false;
}

bool CGraphAlgo::IsConnected(int iNode1, int iNode2, SearchAlgo Algo)
{
	switch (Algo)
	{
	  case SearchAlgo::BFS: return BFS(iNode1, iNode2);
	  case SearchAlgo::DFS: return DFS(iNode1, iNode2);
	  default: throw runtime_error("CGraphAlgo::IsConnected unhandled");
	} m_pGraph->ResetFlags();
}

map<int, int> CGraphAlgo::Djikstra(int iRoot)
{
	auto Compare = [](Node* N1, Node* N2) { return N1->iVal > N2->iVal; };
	std::priority_queue<Node*, vector<Node*>, decltype(Compare)> Q(Compare); //min priority queue
	Q.push(m_pGraph->GetNodeAt(iRoot));

	map<int, int> Shortest_Path_Map;
	/* Initialize */
	vector<int> Indices = m_pGraph->GetNodeIndices();
	for (int index : Indices) { Shortest_Path_Map.insert({ index, INF }); }

	while (!Q.empty())
	{
		Node *N = Q.top(); Q.pop();
		for (auto Neighbour : N->Connections)
		{
			Edge* E = m_pGraph->GetEdgeAt(iRoot, Neighbour->index);
			assert(E != nullptr);

			int tentative_distance = Shortest_Path_Map.at(Neighbour->index) + E->iWeight;
			if (tentative_distance < Shortest_Path_Map.at(Neighbour->index))
			{
				Q.push(Neighbour.get());
				Shortest_Path_Map.at(Neighbour->index) = tentative_distance;
			}
        }
	} return Shortest_Path_Map;
}

