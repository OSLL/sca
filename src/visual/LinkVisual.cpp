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
#include "StringConstants.h"

#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <qmath.h>

LinkVisual::LinkVisual(Link *obj) :
    ObjectVisual(obj, LINK),
    m_sourceArrow(NULL),
    m_destinArrow(NULL),
    m_annotation(NULL),
    m_source(QPointF(0, 0)),
    m_destin(QPointF(0, 0))
{
    QString annotation = obj->getAnnotation();
    setFlags(QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptedMouseButtons(0);
    setZValue(-1);
    setPen(DEFAULT_LINK_PEN);
    setAnnotation(annotation);
}

LinkVisual::~LinkVisual()
{
    delete m_sourceArrow;
    delete m_destinArrow;

    qDebug() << "Removing link";
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
            if (m_filtered)
            {
                setPen(FILTERED_LINK_PEN);
            }
            else
            {
                setPen(DEFAULT_LINK_PEN);
            }
        }
    }
    return ObjectVisual::itemChange(change, value);
}

void LinkVisual::refreshGeometry(QPointF from, QPointF to)
{
    prepareGeometryChange();

    m_source = from;

    m_destin = to;

    QPointF pos = (m_source + m_destin) / 2;

    QPointF begin(m_source - pos);
    QPointF end(m_destin - pos);

    setPos(pos);

    QLineF line(begin, end);

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
    return str.createStroke(path);
}

void LinkVisual::setLine(const QLineF &line)
{
    m_line = line;
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
    d << "LinkVisual: "
      << edge.m_source << " to " << edge.m_destin;
    return d;
}

void LinkVisual::setSourceArrow(QGraphicsPolygonItem *arrow)
{
    if (m_sourceArrow != NULL)
    {
        delete m_sourceArrow;
    }
    m_sourceArrow = arrow;
    m_sourceArrow->setParentItem(this);
}

void LinkVisual::setDestinArrow(QGraphicsPolygonItem *arrow)
{
    if (m_destinArrow != NULL)
    {
        delete m_destinArrow;
    }
    m_destinArrow = arrow;
    m_destinArrow->setParentItem(this);
}

void LinkVisual::setDefaultArrows(bool left)
{
    QVector<QPoint> points;
    points.append(QPoint(-DEFAULT_ARROW_WIDTH/2, -DEFAULT_ARROW_HEIGHT));
    points.append(QPoint(0, 0));
    points.append(QPoint(DEFAULT_ARROW_WIDTH/2, -DEFAULT_ARROW_HEIGHT));

    bool sourceSet = m_source.x() > m_destin.x();
    if (left)
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

    refreshGeometry(m_source, m_destin);
}

void LinkVisual::removeSourceArrow()
{
    if (m_sourceArrow != NULL)
    {
        delete m_sourceArrow;
    }
    m_sourceArrow = NULL;
}

void LinkVisual::removeDestinArrow()
{
    if (m_destinArrow != NULL)
    {
        delete m_destinArrow;
    }
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

void LinkVisual::setSource(const QPointF &source)
{
    m_source = source;
}

void LinkVisual::setDestin(const QPointF &destin)
{
    m_destin = destin;
}

void LinkVisual::setFiltered(bool filtered)
{
    qDebug() << "[LinkVisual]: setFiltered(" << filtered << ")";
    m_filtered = filtered;
    if (filtered)
    {
        setPen(FILTERED_LINK_PEN);
    }
    else
    {
        setPen(DEFAULT_LINK_PEN);
    }
}

void LinkVisual::setAnnotation(QGraphicsTextItem *annotation)
{
    m_annotation = annotation;
}

void LinkVisual::setAnnotation(const QString &str)
{
    deleteAnnotation();
    QGraphicsTextItem *new_ann = new QGraphicsTextItem(this);
    qreal dx = new_ann->boundingRect().center().x(),
            dy = new_ann->boundingRect().center().y()/2;
    new_ann->moveBy(-dx, dy);
    m_annotation = new_ann;

    QString htmlStr("<div style='background-color:#FFFFF0;'>" + str + "</div>");
    m_annotation->setHtml(htmlStr);
}
