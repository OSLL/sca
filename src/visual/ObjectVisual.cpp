#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_object(object)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

IScaObject *ObjectVisual::getObject() const
{
    return m_object;
}

void ObjectVisual::setObject(IScaObject *object)
{
    m_object = object;
}




