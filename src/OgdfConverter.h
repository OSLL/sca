#ifndef OGDFCONVERTER_H
#define OGDFCONVERTER_H
#include "GraphScene.h"

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>

#include <QList>
#include "visual/Node.h"

class OgdfConverter
{
public:
    OgdfConverter(GraphScene *graphVisual);
    ogdf::Graph *convert();
private:
    GraphScene *m_sourceGraph;
};

#endif // OGDFCONVERTER_H
