#ifndef GRAPHPLANARIZER_H
#define GRAPHPLANARIZER_H

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/module/LayoutModule.h>

using namespace ogdf;

class GraphPlanarizer
{
public:
    GraphPlanarizer(Graph *graph, GraphAttributes *graphAttr);
    LayoutModule *layout() const;
    void setLayout(LayoutModule *layout);

    GraphAttributes *getGraphAttr() const;
    void setGraphAttr(GraphAttributes *graphAttr);

    Graph *getGraph() const;
    void setGraph(Graph *graph);

private:
    Graph *m_graph;
    GraphAttributes *m_graphAttr;
    LayoutModule *m_layout;
};

#endif // GRAPHPLANARIZER_H
