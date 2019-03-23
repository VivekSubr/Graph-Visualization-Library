#include "Graph.h"
#include "boost\filesystem.hpp"

#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

enum class GraphOutType { PNG };

class CGraphWriter
{
    CGraph m_pGraph;

	boost::filesystem::path WriteDOT();
public:
    CGraphWriter(CGraph&);
    
    void Visualize(GraphOutType);
    CGraphWriter() = default;
};

#endif
