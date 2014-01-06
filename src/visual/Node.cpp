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
#include "GraphScene.h"

Node::Node(QColor standardColor, QColor filterColor, IScaObject *obj) :
    ObjectVisual(obj, NODE),
    m_title(NULL),
    m_standardColor(standardColor),
    m_selectionColor(QColor(m_standardColor.red()  * SELECTION_COLOR_DELTA,
                            m_standardColor.green()* SELECTION_COLOR_DELTA,
                            m_standardColor.blue() * SELECTION_COLOR_DELTA)),
    m_filterColor(filterColor)
{
    setColor(m_standardColor);
    setCacheMode(DeviceCoordinateCache);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setZValue(1);
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
    QString htmlTitle("<div style='background-color:#FFFFF0;'>" + title + "</div>");
    m_title = new QGraphicsTextItem(this);
    m_title->setHtml(htmlTitle);
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
    if (m_title != NULL)
    {
        m_title->setPos(
                    QPointF(-m_title->boundingRect().width()/2, 20)
                    + QPointF(boundingRect().center()));
    }
}

void Node::setFiltered(bool filtered)
{
    m_filtered = filtered;
    if (m_filtered)
    {
        setColor(m_filterColor);
    }
    else
    {
        setColor(m_standardColor);
    }
}

void Node::setStandardColor(const QColor &color)
{
    m_standardColor = color;
    m_selectionColor.setBlue(color.blue() * 0.5);
    m_selectionColor.setGreen(color.green() * 0.5);
    m_selectionColor.setRed(color.red() * 0.5);
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
    switch (change) {
    case ItemSelectedHasChanged:
        if (value == true) //It is selected now
        {
            setColor(m_selectionColor);
        }
        else
        {
            if (m_filtered)
            {
                setColor(m_filterColor);
            }
            else
            {
                setColor(m_standardColor);
            }
        }
    default:
        break;
    };

    return ObjectVisual::itemChange(change, value);
}
