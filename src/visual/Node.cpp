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

#include "Node.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QGraphicsScene>
#include <QTextDocument>

Node::Node(const QPointF &coords, IScaObject *object) :
    ObjectVisual(object),
    m_title(NULL)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
}

QPointF Node::pos() const
{
    return m_rect.center();
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
        scene()->removeItem(m_title);
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
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_title != NULL)
    {
        m_title->setPos(pos() + QPointF(-m_title->boundingRect().width()/2, 20));
    }
}

QRectF Node::boundingRect() const
{
    return m_rect;
}
