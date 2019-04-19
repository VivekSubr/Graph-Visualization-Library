#include "GraphAlgo.h"
#include <deque>
#include <queue>
#include <functional>
USING_STD using std::deque; using std::map;

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
		if (!It->Flag) DFS(It->index, iNode);
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
	auto Compare = [](pair<int, Node*>& P1, pair<int, Node*>& P2) { return P1.first > P2.first; };
	std::priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, decltype(Compare)> Q(Compare); //min priority queue, with comparision on
	                                                                                               //distance from source  
	Q.push({ 0, m_pGraph->GetNodeAt(iRoot)}); //Distance of root from itself is zero.

	map<int, int> Shortest_Path_Map;
	/* Initialize */
	vector<int> Indices = m_pGraph->GetNodeIndices();
	for (int index : Indices) { Shortest_Path_Map.insert({ index, INF }); }
	Shortest_Path_Map.at(iRoot) = 0;

	while (!Q.empty())
	{
		pair<int, Node*> temp = Q.top(); Q.pop();
		for (auto Neighbour : temp.second->Connections)
		{
			Edge* E = m_pGraph->GetEdgeAt(temp.second->index, Neighbour->index);
			if (E == nullptr || E->Flag) continue; //If edge already visited, continue

			int tentative_distance = temp.first + E->iWeight;
			if (tentative_distance < Shortest_Path_Map.at(Neighbour->index))
			{
				Q.push({ tentative_distance, Neighbour.get() }); 
				Shortest_Path_Map.at(Neighbour->index) = tentative_distance;
			} E->Flag = true;
        }
	} 
	
	m_pGraph->ResetFlags();
	return Shortest_Path_Map;
}

