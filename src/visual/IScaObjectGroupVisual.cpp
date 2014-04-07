/*
 * Copyright 2014  Leonid Skorospelov  leosko94@gmail.com
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
 * \file IScaObjectGroupVisual.cpp
 * \brief IScaObjectGroupVisual implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObjectGroupVisual.h"
#include <QPainter>

IScaObjectGroupVisual::IScaObjectGroupVisual(IScaObjectGroup *obj) :
    Node(DEFAULT_GROUP_COLOR, FILTERED_GROUP_COLOR, obj)
{
    m_rect = QRectF(-DEFAULT_GROUP_VISUAL_WIDTH / 2,
                    -DEFAULT_GROUP_VISUAL_HEIGHT / 2,
                    DEFAULT_GROUP_VISUAL_WIDTH,
                    DEFAULT_GROUP_VISUAL_HEIGHT);
    setTitle(obj->getContent());

    m_firstPos = pos();
}

void IScaObjectGroupVisual::savePoint()
{
    m_firstPos = pos();
}

QPointF IScaObjectGroupVisual::getFirstPos() const
{
    return m_firstPos;
}

void IScaObjectGroupVisual::setFirstPos(const QPoint &pos)
{
    m_firstPos = pos;
}



void IScaObjectGroupVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRect(m_rect);
    Node::paint(painter, option, widget);
}

IScaObjectGroupVisual::~IScaObjectGroupVisual()
{

}
