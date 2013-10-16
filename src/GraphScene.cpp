#include "GraphScene.h"

GraphScene::GraphScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

QGraphicsItem *GraphScene::addNode(IScaObject *object)
{
    QGraphicsItem *node = new Node(object);
    return node;
}
