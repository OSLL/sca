#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_object(object)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

ObjectVisual::~ObjectVisual()
{
    if (m_object != NULL)
        delete m_object;
}

IScaObject *ObjectVisual::getObject() const
{
    return m_object;
}

void ObjectVisual::setObject(IScaObject *object)
{
    m_object = object;
}




