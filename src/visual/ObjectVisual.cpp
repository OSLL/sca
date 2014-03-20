#include "ObjectVisual.h"
#include "../GraphScene.h"
#include <QDebug>

ObjectVisual::ObjectVisual(IScaObject *obj, ObjectVisualType type, QGraphicsItem *parent):
    QAbstractGraphicsShapeItem(parent),
    m_selected(false),
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
    if (str.isEmpty())
        return;

    QGraphicsTextItem *new_ann = new QGraphicsTextItem(this);

    QString htmlStr("<div style='background-color:#FFFFF0;'>" + str + "</div>");
    new_ann->setHtml(htmlStr);
    new_ann->setZValue(-2);

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

bool ObjectVisual::isSelected() const
{
    return m_selected;
}

void ObjectVisual::setSelected(bool arg)
{
    m_selected = arg;
    refreshColor();
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

bool ObjectVisual::isFiltered() const
{
    return m_filtered;
}

void ObjectVisual::setFiltered(bool filtered)
{
    qDebug() << "[ObjectVisual]: setFiltered(" << filtered << ")";
    m_filtered = filtered;
    refreshColor();
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
    case QGraphicsItem::ItemSelectedChange:
        {
            m_selected = value.toBool();
            refreshColor();
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

void ObjectVisual::setX(qreal x)
{
    QAbstractGraphicsShapeItem::setX(x);
    foreach (int linkId, m_links)
    {
        scene()->refreshLinkPos(linkId);
    }
}

void ObjectVisual::setY(qreal y)
{
    QAbstractGraphicsShapeItem::setY(y);
    foreach (int linkId, m_links)
    {
        scene()->refreshLinkPos(linkId);
    }
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
    d << "Node(type=" << node.getType()
      << ";cons=" << node.m_links.size()
      << ";(" << node.pos().x() << ";" << node.pos().y() << "));";
    return d;
}
