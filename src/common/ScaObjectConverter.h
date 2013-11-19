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
 * \file ScaObjectConverter.h
 * \brief Header of ScaObjectConverter
 * \todo Fix canConvert(Node *obj, IScaObject::IScaObjectType toType)
 * \todo Fix ScaObjectConverter
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _ScaObjectConverter_H_A80D37F3_681F_400A_8E4B_4BE4E91A326E_INCLUDED_
#define _ScaObjectConverter_H_A80D37F3_681F_400A_8E4B_4BE4E91A326E_INCLUDED_

class IScaObjectTextBlockVisual;
class IScaObjectIdentifierVisual;
class IScaObjectFileVisual;
class IScaObjectIdentifier;
class IScaObjectTextBlock;
class ObjectVisual;
class Node;
class GraphModel;
#include "common/IScaObject.h"

/*!
 * Class description. May use HTML formatting
 *
 */
class ScaObjectConverter
{
public:
    explicit ScaObjectConverter();

    ~ScaObjectConverter();

    bool canConvert(IScaObject::IScaObjectType fromType, IScaObject::IScaObjectType toType);

    IScaObject *convert(IScaObject *obj, IScaObject::IScaObjectType toType);

    //    quint64 makeTextBlockFromIdentifier(IScaObjectIdentifierVisual *obj, bool autoDel = false);
    IScaObjectTextBlock *makeTextBlockFromIdentifier(IScaObjectIdentifier *obj, bool autoDel = false);

    // TODO (Zo0ER) we need this functions or not? Anyway fix it later
//    quint64 makeIdentifierFromBlock(IScaObjectTextBlockVisual *obj, bool autoDel = false);
    IScaObjectIdentifier *makeIdentifierFromBlock(IScaObjectTextBlock *obj, bool autoDel = false);
}; // class ScaObjectConverter
  

#endif //_ScaObjectConverter_H_A80D37F3_681F_400A_8E4B_4BE4E91A326E_INCLUDED_

