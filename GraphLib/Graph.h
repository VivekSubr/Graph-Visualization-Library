#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "boost\functional\hash.hpp"
#include <memory>
#include <tuple>
#include <initializer_list>
#include <stdexcept>
#pragma once

#define INF 0xFFFF
#define USING_STD using std::string; using std::pair; using std::vector; using std::runtime_error;
#define USING_STD_MEMORY using std::shared_ptr;

class Node
{
public:
	int  index;
	bool Flag;
	int  iVal;
	int  iprevindex;
	std::string sLabel;
	std::unordered_set<std::shared_ptr<Node>> Connections; //set, so as to not repeat Nodes.

	Node() : index(-1), Flag(false), iVal(INF), iprevindex(-1)
	{
	}

	Node(int i, std::string& Label) : Flag(false), iVal(INF), iprevindex(-1)
	{
		index  = i;
		sLabel = Label;
	}
};

class Edge
{
public:
	int  iWeight;
	Node *Node1, *Node2;
	bool Flag;
	Edge() : Node1(nullptr), Node2(nullptr), iWeight(-1), Flag(false)
	{
	}

	Edge(Node* N1, Node* N2, int W) : Node1(N1), Node2(N2), iWeight(W), Flag(false)
	{
	}
};

enum class GraphType { UnDirected, Directed };

class CGraph 
{
	struct hash_pair //for unordered_map of pairs
	{
		template<class T1, class T2>
		size_t operator()(const std::pair<T1, T2>& P) const
		{
			size_t seed = 0;
			boost::hash_combine(seed, P.first);
			boost::hash_combine(seed, P.second);
			return seed;
		}
	}; 

	std::unordered_map<int, std::shared_ptr<Node>>                              m_AdjList;
	std::unordered_map<std::pair<int, int>, std::shared_ptr<Edge>, hash_pair>   m_Edges;
	GraphType                                                                   m_Type;

	CGraph() = default;
public:
	CGraph(GraphType);

	void AddNode(std::shared_ptr<Node>&);
	void AddNode(int, std::string);
	void AddNodes(std::initializer_list<std::pair<int, std::string>>&&); //rvalue

	void AddEdge(int, int, int = 1); //index1, index2, weight
	void AddEdges(std::initializer_list<std::tuple<int, int, int>>&&); //index1, index2, weight

	Node*     GetNodeAt(int);
	Edge*     GetEdgeAt(int, int);
	void      ResetFlags();
	std::vector<int> GetNodeIndices();
	GraphType GetType() { return m_Type; }
     
	~CGraph() = default;
};

