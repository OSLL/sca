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
 * \file IScaObjectTextBlockVisual.h
 * \brief Header of IScaObjectTextBlockVisual
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#ifndef _IScaObjectTextBlockVisual_H_CF304BAB_7922_4297_B374_6D8031EFE75B_INCLUDED_
#define _IScaObjectTextBlockVisual_H_CF304BAB_7922_4297_B374_6D8031EFE75B_INCLUDED_

#include "Node.h"
#include "common/IScaObjectTextBlock.h"

/*!
 * Class description. May use HTML formatting
 *
 */
class IScaObjectTextBlockVisual : public Node
{
public:
    explicit IScaObjectTextBlockVisual(const QPointF &coords, IScaObjectTextBlock *object);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~IScaObjectTextBlockVisual();

private:

}; // class IScaObjectTextBlockVisual


#endif //_IScaObjectTextBlockVisual_H_CF304BAB_7922_4297_B374_6D8031EFE75B_INCLUDED_

