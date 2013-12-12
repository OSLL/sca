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
 * \file Node.h
 * \brief Header of Node
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#ifndef _Node_H_E23A4930_0A72_4232_958D_F40D53C73449_INCLUDED_
#define _Node_H_E23A4930_0A72_4232_958D_F40D53C73449_INCLUDED_

#include "visual/ObjectVisual.h"
#include "NumericalConstants.h"
#include <QGraphicsTextItem>


/*!
 * Class description. May use HTML formatting
 *
 */

class LinkVisual;

class Node : public ObjectVisual
{
public:
    explicit Node(QColor standardColor, IScaObject *obj);
    ~Node();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QRectF getRect() const;
    void setRect(const QRectF &rect);

    QGraphicsTextItem *getTitle() const;
    void setTitle(QGraphicsTextItem *title);
    void setTitle(const QString &title);

    void removeTitle();

    QColor getColor() const;
    void setColor(const QColor &color);
protected:
    QRectF m_rect;
    QGraphicsTextItem *m_title;
    QColor m_standardColor;
    QColor m_selectionColor;
    QColor m_filterColor;

}; // class Node
#endif //_Node_H_E23A4930_0A72_4232_958D_F40D53C73449_INCLUDED_
