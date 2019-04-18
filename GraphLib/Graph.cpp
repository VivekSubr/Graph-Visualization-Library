#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <deque>
USING_STD
USING_STD_MEMORY

CGraph::CGraph(GraphType Type) : m_Type(Type)
{
}

void CGraph::AddNode(shared_ptr<Node>& pNode)
{
	if (pNode->index == -1) throw runtime_error("Node ill formed");
	m_AdjList.insert({ pNode->index, pNode });
}

void CGraph::AddNode(int index, string sName)
{
	m_AdjList.insert({ index, std::make_shared<Node>(index, sName) });
}

void CGraph::AddNodes(std::initializer_list<pair<int, string>>&& InitList)
{
	for (auto Pair : InitList)
	{
		m_AdjList.insert({ Pair.first, std::make_shared<Node>(Pair.first, Pair.second) });
	}
}

void CGraph::AddEdge(int index1, int index2, int iWeight)
{
	m_AdjList.at(index1)->Connections.insert(m_AdjList.at(index2));
	m_AdjList.at(index2)->Connections.insert(m_AdjList.at(index1));

	if (m_Edges.find(pair<int, int>(index2, index1)) != m_Edges.end()) return; //unordered_map, so all these lookups O(1)... 

	std::shared_ptr<Edge> pEdge(new Edge(m_AdjList.at(index1).get(), m_AdjList.at(index2).get(), iWeight));
	m_Edges.insert({ pair<int, int>(index1, index2), pEdge });
}

void CGraph::AddEdges(std::initializer_list<std::tuple<int, int, int>>&& InitList)
{
	for (auto Edge : InitList) { AddEdge(std::get<0>(Edge), std::get<1>(Edge), std::get<2>(Edge)); }
}

Node* CGraph::GetNodeAt(int index)
{
	return m_AdjList.at(index).get();
}

void CGraph::ResetFlags()
{
	std::for_each(m_AdjList.begin(), m_AdjList.end(), [](auto MapEle) { MapEle.second->Flag = false; });
	std::for_each(m_Edges.begin(), m_Edges.end(), [](auto MapEle) { MapEle.second->Flag = false; });
}

Edge* CGraph::GetEdgeAt(int Node1, int Node2)
{
	if (m_Edges.find(pair<int, int>(Node1, Node2)) != m_Edges.end())
	{
		return m_Edges.at(pair<int, int>(Node1, Node2)).get();
	} 
	else if (m_Edges.find(pair<int, int>(Node2, Node1)) != m_Edges.end())
	{
		return m_Edges.at(pair<int, int>(Node2, Node1)).get();
	} return nullptr;
}

std::vector<int> CGraph::GetNodeIndices()
{
	std::vector<int> Indices;
	for (auto Pair : m_AdjList) { Indices.push_back(Pair.first); }
	return Indices;
}
