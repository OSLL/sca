#include "ObjectVisual.h"
#include "GraphScene.h"
#include <QDebug>

ObjectVisual::ObjectVisual(IScaObject *obj, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_filtered(false)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);

    setToolTip(obj->getInfo(OBJECT_TOOLTIP_PATTERN));
}

ObjectVisual::~ObjectVisual()
{
}

QVariant ObjectVisual::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
    case ItemPositionChange:
        foreach (quint32 linkId, m_links)
        {
            scene()->refreshLinkPos(linkId);
        }
        break;
    default:
        {
            break;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void ObjectVisual::addLink(quint32 linkId)
{
    qDebug() << "Appending link #" << linkId;
    m_links.append(linkId);
    scene()->refreshLinkPos(linkId);
}

QList<quint32> ObjectVisual::getLinks() const
{
    return m_links;
}

void ObjectVisual::setLinks(const QList<quint32> &links)
{
    m_links = links;
}

void ObjectVisual::setFiltered(bool filtered)
{
    m_filtered = filtered;
    if(m_filtered)
        setBrush(FILTER_BRUSH);
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
