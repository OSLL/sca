#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent), m_object(object), m_type(OBJECT)
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




