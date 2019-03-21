#include "Graph.h"
#include "boost\filesystem.hpp"

#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

class CGraphWriter
{
    CGraph m_pGraph;

	boost::filesystem::path WriteDOT();
public:
    CGraphWriter(CGraph&);
    
    void Visualize();
    CGraphWriter() = default;
};

#endif
