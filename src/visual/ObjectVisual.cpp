#include "ObjectVisual.h"
#include "GraphScene.h"

ObjectVisual::ObjectVisual(ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);
}

ObjectVisual::~ObjectVisual()
{
}

GraphScene *ObjectVisual::scene() const
{
    return static_cast<GraphScene *>(QGraphicsItem::scene());
}

ObjectVisual::ObjectVisualType ObjectVisual::getType() const
{
    return m_type;
}

void ObjectVisual::setType(const ObjectVisualType &type)
{
    m_type = type;
}
