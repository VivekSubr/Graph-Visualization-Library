#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <deque>
#include "Utility.h"
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
	try
	{
		m_AdjList.at(index1)->Connections.push_back(m_AdjList.at(index2));
		m_AdjList.at(index2)->Connections.push_back(m_AdjList.at(index1));

		Edge pEdge;
		pEdge.Node1   = m_AdjList.at(index1).get();
		pEdge.Node2   = m_AdjList.at(index2).get();
		pEdge.iWeight = iWeight;

		m_EdgeAr.push_back(pEdge);
	}
	catch (std::out_of_range& ex) { throw ex; }
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
}

Edge* CGraph::GetEdgeAt(int Node1, int Node2)
{
	for (auto Edge = m_EdgeAr.begin(); Edge != m_EdgeAr.end(); Edge++)
	{
		if (Edge->Node1->index == Node1 || Edge->Node2->index == Node2) return &*Edge;
		if (Edge->Node1->index == Node2 || Edge->Node2->index == Node1) return &*Edge;
	} return nullptr;
}

std::vector<int> CGraph::GetNodeIndices()
{
	std::vector<int> Indices;
	for (auto Pair : m_AdjList) { Indices.push_back(Pair.first); }
	return Indices;
}
