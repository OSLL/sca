#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_object(object)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);
}

ObjectVisual::~ObjectVisual()
{
}


ObjectVisual::ObjectVisualType ObjectVisual::getType() const
{
    return m_type;
}

void ObjectVisual::setType(const ObjectVisualType &type)
{
    m_type = type;
}

IScaObject *ObjectVisual::getObject() const
{
    return m_object;
}

void ObjectVisual::setObject(IScaObject *object)
{
    m_object = object;
}

IScaObject::IScaObjectType ObjectVisual::getObjectType() const
{
    return m_object->getType();
}
