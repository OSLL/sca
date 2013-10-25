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

LinkVisual::LinkVisual(Node *source, Node *dest) :
    ObjectVisual(new Link(source->getObject(), dest->getObject()), EDGE),
    m_source(source),
    m_dest(dest)
{
    m_source->addLink(this);
    m_dest->addLink(this);

    refreshGeometry();

    setFlags(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptedMouseButtons(0);
    setPen(QPen(QBrush(Qt::black), 9, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void LinkVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    refreshGeometry();
    painter->setPen(pen());
    painter->drawLine(m_line);
}

QVariant LinkVisual::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}

void LinkVisual::refreshGeometry()
{
    prepareGeometryChange();
    qreal sourceX = m_source->x() + m_source->boundingRect().center().x();
    qreal sourceY = m_source->y() + m_source->boundingRect().center().y();

    qreal destX = m_dest->x() + m_dest->boundingRect().center().x();
    qreal destY = m_dest->y() + m_dest->boundingRect().center().y();

    qreal posX = (sourceX + destX) / 2;
    qreal posY = (sourceY + destY) / 2;

    QPointF begin(sourceX - posX, sourceY - posY);
    QPointF end(destX - posX, destY - posY);

    setX(posX);
    setY(posY);

    setLine(QLineF(begin, end));
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
    return str.createStroke(path);
}

void LinkVisual::setLine(const QLineF &line)
{
    m_line = line;
}
