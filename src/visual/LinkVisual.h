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
 * \file LinkVisual.h
 * \brief Header of LinkVisual
 * \todo Fix disconnectingFrom(Node *)
 * \todo Fix changeNode(Node *oldNode, Node *newNode)
 * \todo Fix setAnnotation(QString &)
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#ifndef _LinkVisual_H_3810BBA1_46FC_4CF9_95DB_5C510A604AA0_INCLUDED_
#define _LinkVisual_H_3810BBA1_46FC_4CF9_95DB_5C510A604AA0_INCLUDED_

#include "ObjectVisual.h"
#include "visual/Node.h"
#include "../common/Link.h"

/*!
 * Class description. May use HTML formatting
 *
 */
class LinkVisual : public ObjectVisual
{
public:
    LinkVisual(Link *obj);
    ~LinkVisual();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void refreshGeometry(QPointF from, QPointF to);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setLine(const QLineF &line);

    friend QDebug operator<< (QDebug d, LinkVisual &edge);

    QGraphicsPathItem *getSourceArrow();
    QGraphicsPathItem *getDestinArrow();

    void setSourceArrow(QGraphicsPathItem *arrow);
    void setDestinArrow(QGraphicsPathItem *arrow);
    void setDefaultArrows(bool left);
    void setDefaultArrows(bool source, bool destin);

    void removeSourceArrow();
    void removeDestinArrow();

    QPointF getSource();
    QPointF getDestin();
    void setSource(const QPointF &source);
    void setDestin(const QPointF &destin);

    void setStandardColor(const QColor &color);
    QColor getStandardColor() const;

    void setPen(const QPen &pen);
    void refreshColor();
private:
    QLineF m_line;
    QGraphicsPathItem *m_sourceArrow;
    QGraphicsPathItem *m_destinArrow;

    QPen m_standardPen;
    QPen m_selectionPen;
    QPen m_filterPen;
    QPointF m_source;
    QPointF m_destin;
}; // class LinkVisual


#endif //_LinkVisual_H_3810BBA1_46FC_4CF9_95DB_5C510A604AA0_INCLUDED_

