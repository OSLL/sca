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
#include "LinkVisual.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QGraphicsScene>
#include <QTextDocument>
#include "../GraphScene.h"

Node::Node(QColor standardColor, QColor filterColor, IScaObject *obj) :
    ObjectVisual(obj, NODE),
    m_title(NULL),
    m_filterColor(filterColor)
{
    setStandardColor(standardColor);
    setCacheMode(DeviceCoordinateCache);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setZValue(1);

    setTitle(obj->getTitle());
}

Node::~Node()
{
    qDebug() << "Removing " << *this;
    removeTitle();
}


QRectF Node::getRect() const
{
    return m_rect;
}

void Node::setRect(const QRectF &rect)
{
    m_rect = rect;
}

void Node::setSize(const QSize &size)
{
    m_rect.setSize(size);
    if (m_title != NULL)
    {
        m_title->setY(m_rect.height() / 2);
    }
    if (m_annotation != NULL)
    {
        m_annotation->setY(m_rect.height() / 2 + m_annotation->boundingRect().height());
    }
    m_rect.moveTo(-size.width()/2, -size.height()/2);
}

QGraphicsTextItem *Node::getTitle() const
{
    return m_title;
}

void Node::removeTitle()
{
    if (m_title != NULL)
    {
        if(scene() != NULL)
        {
            scene()->removeItem(m_title);
        }
        delete m_title;
        m_title = NULL;
    }
}

void Node::setTitle(const QString &title)
{

    removeTitle();
    QString temp = title;
    if(temp.length() > MAX_TITLE_LENGTH)
    temp = temp.mid(0, MAX_TITLE_LENGTH) + "...";
    temp    .replace('&', "&amp;")
            .replace('>', "&gt;")
            .replace('<', "&lt;");
    QString htmlTitle("<div style='background-color:#FFFFF0;'>"
                      + temp
                      + "</div>");
    m_title = new QGraphicsTextItem(this);
    m_title->setHtml(htmlTitle);
    m_title->setX(-m_title->boundingRect().width() / 2);
    m_title->setY(m_rect.height() / 2);
}

void Node::setTitle(QGraphicsTextItem *title)
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
}

void Node::refreshColor()
{
    qDebug() << "[Node]: refreshColor() ";
    if (isFiltered())
    {
        setColor(m_filterColor);
        return;
    }
    else if (isSelected())
    {
        setColor(m_selectionColor);
        return;
    }
    else
    {
        setColor(m_standardColor);
    }
}

void Node::setStandardColor(const QColor &color)
{
    m_standardColor = color;
    m_selectionColor = m_standardColor.darker(150);
    setColor(m_selectionColor);
}

QColor Node::getStandardColor() const
{
    return m_standardColor;
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
    return ObjectVisual::itemChange(change, value);
}
