#include "ObjectVisual.h"
#include "GraphScene.h"
#include <QDebug>

ObjectVisual::ObjectVisual(ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_filtered(false)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);
}

ObjectVisual::~ObjectVisual()
{
}

void ObjectVisual::disconnectLink(int linkId)
{
    if (m_links.removeOne(linkId))
    {
        qDebug() << "Removing link from" << *this;
    }
    else
    {
        qDebug() << "Tried to remove unexisting link from" << *this;
    }
}

QVariant ObjectVisual::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
    case ItemPositionChange:
        foreach (int linkId, m_links)
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

void ObjectVisual::addLink(int linkId)
{
    qDebug() << "Appending link #" << linkId;
    m_links.append(linkId);
    scene()->refreshLinkPos(linkId);
}

QList<int> ObjectVisual::getLinks() const
{
    return m_links;
}

void ObjectVisual::setLinks(const QList<int> &links)
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

QDebug operator<<(QDebug d, ObjectVisual &node)
{
    d << "Node(type=" << node.getType() << ";cons=" << node.m_links.size() << ");";
    return d;
}
