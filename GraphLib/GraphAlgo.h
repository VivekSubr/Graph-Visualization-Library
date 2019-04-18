#include "Graph.h"
#include <map>
#ifndef GRAPH_ALGO_H
#define GRAPH_ALGO_H

enum class SearchAlgo { BFS, DFS };

class CGraphAlgo
{
	CGraph* m_pGraph;

	bool BFS(int, int); 
	bool DFS(int, int); 

public:
	CGraphAlgo() = delete;
	CGraphAlgo(CGraph*);

	bool                IsConnected(int, int, SearchAlgo);
	std::map<int, int>  Djikstra(int); // Map of distance from source to key node

	~CGraphAlgo() = default;
};

#endif

