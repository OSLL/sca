#include "ObjectVisual.h"
#include "GraphScene.h"
#include <qDebug>

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

void ObjectVisual::addLinkFrom(quint32 linkId)
{
    m_linksFrom.append(linkId);
    scene()->refreshLinkPosFrom(linkId, pos());
}

void ObjectVisual::addLinkTo(quint32 linkId)
{
    m_linksTo.append(linkId);
    scene()->refreshLinkPosTo(linkId, pos());
}
QList<quint32> ObjectVisual::getLinksFrom() const
{
    return m_linksFrom;
}

void ObjectVisual::setLinksFrom(const QList<quint32> &linksFrom)
{
    m_linksFrom = linksFrom;
}


QList<quint32> ObjectVisual::getLinksTo() const
{
    return m_linksTo;
}

void ObjectVisual::setLinksTo(const QList<quint32> &linksTo)
{
    m_linksTo = linksTo;
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
