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
 * \file IScaObjectDirectoryVisual.cpp
 * \brief IScaObjectDirectoryVisual implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObjectDirectoryVisual.h"
#include <QPainter>

IScaObjectDirectoryVisual::IScaObjectDirectoryVisual(IScaObjectDirectory *obj) :
    Node(DEFAULT_DIR_COLOR, FILTERED_DIR_COLOR, obj)
{
    m_rect = QRectF(-DEFAULT_DIR_VISUAL_WIDTH / 2,
                    -DEFAULT_DIR_VISUAL_HEIGHT / 2,
                    DEFAULT_DIR_VISUAL_WIDTH,
                    DEFAULT_DIR_VISUAL_HEIGHT);
    QFileInfo fileInfo = obj->getFile();
    if (fileInfo.isRoot())
        setTitle(fileInfo.absoluteFilePath().section('/', 0, 0));
    else
        setTitle(fileInfo.absoluteFilePath().section('/', -1));
}

void IScaObjectDirectoryVisual::paint(QPainter *painter,
                                      const QStyleOptionGraphicsItem *option,
                                      QWidget *widget)
{
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(m_rect);
    Node::paint(painter, option, widget);
}

IScaObjectDirectoryVisual::~IScaObjectDirectoryVisual()
{

}
