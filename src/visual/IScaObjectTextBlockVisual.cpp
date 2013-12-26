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
 * \file IScaObjectTextBlockVisual.cpp
 * \brief IScaObjectTextBlockVisual implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObjectTextBlockVisual.h"
#include <QPainter>

IScaObjectTextBlockVisual::IScaObjectTextBlockVisual(IScaObjectTextBlock *obj) :
    Node(DEFAULT_TEXT_BLOCK_COLOR, FILTERED_TEXT_BLOCK_COLOR, obj)
{
    QString text = obj->getText();
    m_rect = QRectF(-DEFAULT_TEXT_BLOCK_VISUAL_WIDTH / 2,
                    -DEFAULT_TEXT_BLOCK_VISUAL_HEIGHT / 2,
                    DEFAULT_TEXT_BLOCK_VISUAL_WIDTH,
                    DEFAULT_TEXT_BLOCK_VISUAL_HEIGHT);

    if(text.size() > MAX_TITLE_LENGTH)
    {
        text = text.mid(0, MAX_TITLE_LENGTH) + "...";
    }
    setTitle(text);
}

void IScaObjectTextBlockVisual::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawEllipse(m_rect);
    Node::paint(painter, option, widget);
}

IScaObjectTextBlockVisual::~IScaObjectTextBlockVisual()
{

}
