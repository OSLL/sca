#include "OgdfConverter.h"


OgdfConverter::OgdfConverter(GraphScene *graphVisual):
    m_sourceGraph(graphVisual)
{
}

ogdf::Graph *OgdfConverter::convert()
{
    ogdf::Graph *graph = new ogdf::Graph();
    ogdf::GraphAttributes graphAttr(*graph,
                                    ogdf::GraphAttributes::nodeGraphics |
                                    ogdf::GraphAttributes::edgeGraphics );

    QHash<int, ObjectVisual *> *objects = m_sourceGraph->getObjects();
    QList<int> links;

    QHash<int, ogdf::NodeElement *  > nodes;

    foreach(int key, objects->keys())
    {
        ObjectVisual *object = (*objects)[key];

        if(object->getType() == ObjectVisual::NODE)
        {
            Node *node = static_cast<Node *>(object);

            ogdf::NodeElement *newNode  = graph->newNode(key);
            graphAttr.x(newNode) = node->pos().x();
            graphAttr.y(newNode) = node->pos().y();
            graphAttr.width(newNode) = node->boundingRect().width();
            graphAttr.height(newNode) = node->boundingRect().height();

            nodes[key] = newNode;
        }

        if(object->getType() == ObjectVisual::LINK)
        {
            links.append(key);
        }

    }

    foreach(int linkId, links)
    {
        int source = m_sourceGraph->getLinkSource(linkId);
        int destin = m_sourceGraph->getLinkDestin(linkId);
        graph->newEdge(nodes[source], nodes[destin], linkId);
    }

    return graph;
}
