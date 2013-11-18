/*
 * Copyright 2013  Nikita Razdobreev  exzo0mex@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/*! ---------------------------------------------------------------
 *
 * \file Node.cpp
 * \brief Node implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "visual/Node.h"
#include "visual/LinkVisual.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QGraphicsScene>
#include <QTextDocument>

Node::Node(IScaObject *object, QColor standardColor) :
    ObjectVisual(object, NODE),
    m_title(NULL),
    m_standardColor(standardColor),
    m_selectionColor(QColor(m_standardColor.red()  * SELECTION_COLOR_DELTA,
                            m_standardColor.green()* SELECTION_COLOR_DELTA,
                            m_standardColor.blue() * SELECTION_COLOR_DELTA))
{
    setColor(m_standardColor);
    setCacheMode(DeviceCoordinateCache);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setZValue(1);
}

Node::~Node()
{
    qDebug() << "Removing " << *this;
    foreach(LinkVisual *link, m_links)
    {
        delete link;
    }
    removeTitle();
}

void Node::addLink(LinkVisual *link)
{
    m_links.append(link);
}

QList<LinkVisual *> Node::getLinks()
{
    return m_links;
}

void Node::disconnectLink(LinkVisual *link)
{
    m_links.takeAt(m_links.indexOf(link));
}

QRectF Node::getRect() const
{
    return m_rect;
}

void Node::setRect(const QRectF &rect)
{
    m_rect = rect;
}

QGraphicsSimpleTextItem *Node::getTitle() const
{
    return m_title;
}

void Node::removeTitle()
{
    if (m_title != NULL)
    {
        qDebug() << "Removing title";
        scene()->removeItem(m_title);
        delete m_title;
        m_title = NULL;
        qDebug() << "Removed title";
    }
}

void Node::setTitle(const QString &title)
{
    removeTitle();
    m_title = new QGraphicsSimpleTextItem(title, this);
}

void Node::setTitle(QGraphicsSimpleTextItem *title)
{
    removeTitle();
    m_title = title;
    m_title->setParentItem(this);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    qDebug() << pos();
    if (m_title != NULL)
    {
        m_title->setPos(
                    QPointF(-m_title->boundingRect().width()/2, 20)
                    + QPointF(boundingRect().center()));
    }
}

QRectF Node::boundingRect() const
{
    return m_rect;
}

QColor Node::getColor() const
{
    return brush().color();
}

void Node::setColor(const QColor &color)
{
    setBrush(color);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionChange:
        foreach (LinkVisual *link, m_links)
            link->refreshGeometry();
        break;
    case ItemSelectedHasChanged:
        if (value == true) //It is selected now
        {
            setColor(m_selectionColor);
        }
        else
        {
            setColor(m_standardColor);
        }
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

QDebug operator<<(QDebug d, Node &node)
{
    d << "Node: "
      << "type: " << node.m_type
      << ", name: " << node.getTitle()->text()
      << ", links: " << node.m_links.size();
    return d;
}
