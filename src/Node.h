#ifndef NODE_H
#define NODE_H
#include "ObjectVisual.h"
#include "NumericalConstants.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QRectF>

class Node : public ObjectVisual
{
public:
    Node(IScaObject *object);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    QRectF getRect() const;
    void setRect(const QRectF &rect);

private:
    QRectF m_rect;

};
#endif // NODE_H
