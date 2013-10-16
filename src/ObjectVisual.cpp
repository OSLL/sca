#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object)
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




