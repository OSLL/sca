/*
 * Copyright 2013  Leonid Skorospelov  leosko94@gmail.com
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
 * \file LinkVisual.cpp
 * \brief LinkVisual implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "visual/LinkVisual.h"

#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <qmath.h>

LinkVisual::LinkVisual(Node *source, Node *dest) :
    ObjectVisual(new Link(source->getObject(), dest->getObject()), EDGE),
    m_sourceNode(source),
    m_destinNode(dest),
    m_sourceArrow(NULL),
    m_destinArrow(NULL),
    m_annotation(NULL)
{
    m_sourceNode->addLink(this);
    m_destinNode->addLink(this);


    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptedMouseButtons(0);
    setZValue(-1);
    setPen(DEFAULT_LINK_PEN);

    m_sourceRadius = qSqrt(qPow(m_sourceNode->boundingRect().width(),2)
                           + qPow(m_sourceNode->boundingRect().height(),2)) / 2 + 1;
    m_destinRadius = qSqrt(qPow(m_destinNode->boundingRect().width(),2)
                           + qPow(m_destinNode->boundingRect().height(),2)) / 2 + 1;
    refreshGeometry();
}

LinkVisual::~LinkVisual()
{
    qDebug() << "Removing " << *this;
    m_sourceNode->disconnectLink(this);
    m_destinNode->disconnectLink(this);
}

void LinkVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(qFuzzyCompare(m_line.length(), qreal(0.0)))
        return;

    painter->setPen(pen());
    painter->drawLine(m_line);
}

QVariant LinkVisual::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)  //Now it is selected
        {
            setPen(SELECTED_LINK_PEN);
        }
        else    //Now it is unselected
        {
            setPen(DEFAULT_LINK_PEN);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void LinkVisual::refreshGeometry()
{
    if (m_sourceNode == NULL || m_destinNode == NULL)
        return;

    prepareGeometryChange();

    m_source = m_sourceNode->pos();

    m_destin = m_destinNode->pos();

    QPointF pos = (m_source + m_destin) / 2;

    QPointF begin(m_source - pos);
    QPointF end(m_destin - pos);

    setPos(pos);

    QLineF line(begin, end);

    QPointF sourceOffset((line.dx() * m_sourceRadius) / line.length(),
                         (line.dy() * m_sourceRadius) / line.length());
    QPointF destinOffset((line.dx() * m_destinRadius) / line.length(),
                         (line.dy() * m_destinRadius) / line.length());

    if (line.length() > MIN_LINK_LENGTH)
    {
        begin = line.p1() + sourceOffset;
        end = line.p2() - destinOffset;
    }

    qreal angle = -line.angle();


    if (m_sourceArrow != NULL)
    {
        m_sourceArrow->setVisible(line.length() > MIN_LINK_LENGTH);
        m_sourceArrow->setPos(begin);
        m_sourceArrow->setRotation(angle + 90);
    }

    if (m_destinArrow != NULL)
    {
        m_destinArrow->setVisible(line.length() > MIN_LINK_LENGTH);
        m_destinArrow->setPos(end);
        m_destinArrow->setRotation(angle - 90);
    }


    line = QLineF(begin, end);
    setLine(line);
}

QRectF LinkVisual::boundingRect() const
{
    qreal   extra = pen().width() / 2 + 1;

    QPointF p1 = m_line.p1();
    QPointF p2 = m_line.p2();

    qreal left = p1.x();
    qreal top  = p1.y();

    qreal width  = p2.x() - left;
    qreal height = p2.y() - top;

    return  QRectF(left, top, width, height)
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath LinkVisual::shape() const
{
    QPainterPath path;
    QPainterPathStroker str;
    path.moveTo(m_line.p1());
    path.lineTo(m_line.p2());
    str.setWidth(DEFAULT_LINK_WIDTH + LINE_SELECTION_DELTA);
    qDebug() << pos();
    return str.createStroke(path);
}

void LinkVisual::setLine(const QLineF &line)
{
    m_line = line;
}

void LinkVisual::disconnectFrom(Node *node)
{
    qDebug() << "Disconnecting " << *this << " from " << *node;
    if (m_sourceNode == node)
    {
        Link *link = static_cast<Link *>(getObject());
        if (link == NULL)
            return;
        link->setObjectFrom(NULL);
        m_sourceNode = NULL;
    }
    if (m_destinNode == node)
    {
        Link *link = static_cast<Link *>(getObject());
        if (link == NULL)
            return;
        link->setObjectTo(NULL);
        m_destinNode = NULL;
    }
    qDebug() << "Disconnected successfully.";
}

void LinkVisual::changeNode(Node *oldNode, Node *newNode)
{
    qDebug() << *oldNode << *newNode;
    Link *obj = static_cast<Link *>(getObject());
    if (m_sourceNode == oldNode)
    {
        m_sourceNode = newNode;
        obj->setObjectFrom(newNode->getObject());
    }
    if (m_destinNode == oldNode)
    {
        m_destinNode = newNode;
        obj->setObjectTo(newNode->getObject());
    }

    refreshGeometry();
}

QGraphicsPolygonItem *LinkVisual::getSourceArrow()
{
    return m_sourceArrow;
}

QGraphicsPolygonItem *LinkVisual::getDestinArrow()
{
    return m_destinArrow;
}

QDebug operator<<(QDebug d, LinkVisual &edge)
{
    d << "LinkVisual: from "
      << edge.m_sourceNode->getTitle()->text()
      << " to "
      << edge.m_destinNode->getTitle()->text();
    return d;
}

void LinkVisual::setSourceArrow(QGraphicsPolygonItem *arrow)
{
    delete(m_sourceArrow);
    m_sourceArrow = arrow;
    m_sourceArrow->setParentItem(this);
}

void LinkVisual::setDestinArrow(QGraphicsPolygonItem *arrow)
{
    delete(m_destinArrow);
    m_destinArrow = arrow;
    m_destinArrow->setParentItem(this);
}

void LinkVisual::setDefaultArrows(bool left)
{
    QVector<QPoint> points;
    points.append(QPoint(-DEFAULT_ARROW_WIDTH/2, -DEFAULT_ARROW_HEIGHT/2));
    points.append(QPoint(0, DEFAULT_ARROW_HEIGHT/2));
    points.append(QPoint(DEFAULT_ARROW_WIDTH/2, -DEFAULT_ARROW_HEIGHT/2));

    bool sourceSet = m_source.x() > m_destin.x();
    if(left)
    {
        sourceSet = !sourceSet;
    }

    if (sourceSet && (m_sourceArrow == NULL))
    {
        m_sourceArrow = new QGraphicsPolygonItem(QPolygon(points), this);
        m_sourceArrow->setPen(DEFAULT_LINK_PEN);

    }
    else if(m_destinArrow == NULL)
    {
        m_destinArrow = new QGraphicsPolygonItem(QPolygon(points), this);
        m_destinArrow->setPen(DEFAULT_LINK_PEN);
    }

    refreshGeometry();
}

void LinkVisual::removeSourceArrow()
{
    delete(m_sourceArrow);
    m_sourceArrow = NULL;
}

void LinkVisual::removeDestinArrow()
{

    delete(m_destinArrow);
    m_destinArrow = NULL;
}

void LinkVisual::deleteAnnotation()
{
    if (m_annotation != NULL)
    {
        delete m_annotation;
        m_annotation = NULL;
    }
}

QString LinkVisual::getAnnotationText() const
{
    return getObject()->getAnnotation();
}

QPointF LinkVisual::getSource()
{
    return m_source;
}

QPointF LinkVisual::getDestin()
{
    return m_destin;
}

QGraphicsTextItem *LinkVisual::getAnnotation() const
{
    return m_annotation;
}

void LinkVisual::setAnnotation(QGraphicsTextItem *annotation)
{
    m_annotation = annotation;
}

void LinkVisual::setAnnotation(const QString &str)
{
    if (getObject()->getAnnotation() == str)
    {
        return;
    }
    getObject()->setAnnotation(str);
    deleteAnnotation();
    QGraphicsTextItem *new_ann = new QGraphicsTextItem(str, this);
    qreal dx = new_ann->boundingRect().center().x(),
            dy = new_ann->boundingRect().center().y()/2;
    new_ann->moveBy(-dx, dy);
    m_annotation = new_ann;
}

