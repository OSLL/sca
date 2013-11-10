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

IScaObject::IScaObjectType ObjectVisual::getObjectType() const
{
    return m_object->getType();
}

ObjectVisual::ObjectVisualType ObjectVisual::getType() const
{
    return m_type;
}

void ObjectVisual::setType(const ObjectVisualType &type)
{
    m_type = type;
}





