/*
 * Copyright 2013    exzo0mex@gmail.com
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
 * \file IScaObjectBinaryBlockVisual.h
 * \brief Header of IScaObjectBinaryBlockVisual
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectBinaryBlockVisual_H_DF0A8168_00F0_4FC9_A4E4_CE9272C45764_INCLUDED_
#define _IScaObjectBinaryBlockVisual_H_DF0A8168_00F0_4FC9_A4E4_CE9272C45764_INCLUDED_
#include "visual/Node.h"
#include "common/IScaObjectBinaryBlock.h"
/*!
 * Class description. May use HTML formatting
 *
 */
class IScaObjectBinaryBlockVisual: public Node
{
public:
    explicit IScaObjectBinaryBlockVisual(IScaObjectBinaryBlock *obj);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ~IScaObjectBinaryBlockVisual();
private:    

}; // class IScaObjectBinaryBlockVisual


#endif //_IScaObjectBinaryBlockVisual_H_DF0A8168_00F0_4FC9_A4E4_CE9272C45764_INCLUDED_
