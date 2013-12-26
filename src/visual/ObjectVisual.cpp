#include "ObjectVisual.h"
#include "GraphScene.h"
#include <QDebug>

ObjectVisual::ObjectVisual(IScaObject *obj, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_type(type),
    m_filtered(false),
    m_annotation(NULL)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable);
    refreshToolTip(obj);
}

ObjectVisual::~ObjectVisual()
{
}

void ObjectVisual::deleteAnnotation()
{
    if (m_annotation != NULL)
    {
        delete m_annotation;
        m_annotation = NULL;
    }
}

QGraphicsTextItem *ObjectVisual::getAnnotation() const
{
    return m_annotation;
}

void ObjectVisual::setAnnotation(QGraphicsTextItem *annotation)
{
    m_annotation = annotation;
}

void ObjectVisual::setAnnotation(const QString &str)
{
    deleteAnnotation();
    QGraphicsTextItem *new_ann = new QGraphicsTextItem(this);

    QString htmlStr("<div style='background-color:#FFFFF0;'>" + str + "</div>");
    new_ann->setHtml(htmlStr);

    qreal dx = new_ann->boundingRect().center().x(),
          dy = -new_ann->boundingRect().height() - boundingRect().height() / 2;
    if (m_type != LINK)
    {
        new_ann->moveBy(-dx, dy);
    }
    else
    {
        new_ann->moveBy(-dx, 0);
    }
    m_annotation = new_ann;
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

void ObjectVisual::refreshToolTip(IScaObject *obj)
{
    setToolTip(obj->getInfo(OBJECT_TOOLTIP_PATTERN));
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
