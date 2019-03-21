#include <vector>
#include <map>
#include <memory>
#include <tuple>
#include <initializer_list>
#include <stdexcept>
#pragma once

#define INF 0xFFFF
#define USING_STD using std::string; using std::pair; using std::vector; using std::map; using std::runtime_error;
#define USING_STD_MEMORY using std::shared_ptr;

class Node
{
public:
	int  index;
	bool Flag;
	int  iVal;
	int  iprevindex;
	std::string sLabel;
	std::vector<std::shared_ptr<Node>> Connections;

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

	Edge() : Node1(nullptr), Node2(nullptr), iWeight(-1)
	{
	}
};

enum class GraphType { UnDirected, Directed };

class CGraph 
{
	std::map<int, std::shared_ptr<Node>> m_AdjList;
	std::vector<Edge>                    m_EdgeAr;
	GraphType                            m_Type;

	CGraph() = default;
public:
	CGraph(GraphType);

	void AddNode(std::shared_ptr<Node>&);
	void AddNode(int, std::string);
	void AddNodes(std::initializer_list<std::pair<int, std::string>>&&); //rvalue

	void AddEdge(int, int, int = 1);
	void AddEdges(std::initializer_list<std::tuple<int, int, int>>&&);

	Node*     GetNodeAt(int);
	Edge*     GetEdgeAt(int, int);
	void      ResetFlags();
	std::vector<int> GetNodeIndices();
	GraphType GetType() { return m_Type; }
     
	~CGraph() = default;
};

