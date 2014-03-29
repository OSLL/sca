#include "GraphPlanarizer.h"

GraphPlanarizer::GraphPlanarizer(Graph *graph, GraphAttributes *graphAttr):
    m_graph(graph),
    m_graphAttr(graphAttr)
{

}



Graph *GraphPlanarizer::getGraph() const
{
    return m_graph;
}

void GraphPlanarizer::setGraph(Graph *graph)
{
    m_graph = graph;
}

GraphAttributes *GraphPlanarizer::getGraphAttr() const
{
    return m_graphAttr;
}

void GraphPlanarizer::setGraphAttr(GraphAttributes *graphAttr)
{
    m_graphAttr = graphAttr;
}

LayoutModule *GraphPlanarizer::layout() const
{
    return m_layout;
}

void GraphPlanarizer::setLayout(LayoutModule *layout)
{
    m_layout = layout;
}
