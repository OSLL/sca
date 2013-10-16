#include "Node.h"

Node::Node(IScaObject *object): ObjectVisual(object)
{
    m_type = NODE;

    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    m_rect = QRectF(0, 0, DEFAULT_RECT_SIZE, DEFAULT_RECT_SIZE);
}

QRectF Node::boundingRect() const
{
    return m_rect;
}


QRectF Node::getRect() const
{
    return m_rect;
}

void Node::setRect(const QRectF &rect)
{
    m_rect = rect;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(m_rect);
}
