#include "ObjectVisual.h"

ObjectVisual::ObjectVisual(IScaObject *object):
    QGraphicsItem()
{    
    m_object = object;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    m_type = OBJECT;
}
IScaObject *ObjectVisual::getObject() const
{
    return m_object;
}

void ObjectVisual::setObject(IScaObject *object)
{
    m_object = object;
}




