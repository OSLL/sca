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
 * \file ScaObjectConverter.cpp
 * \brief ScaObjectConverter implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "ScaObjectConverter.h"
#include "visual/ObjectVisual.h"
#include "visual/IScaObjectFileVisual.h"
#include "visual/IScaObjectDirectoryVisual.h"
#include "visual/IScaObjectTextBlockVisual.h"
#include "visual/IScaObjectSymbolVisual.h"
#include "visual/IScaObjectLineVisual.h"
#include "visual/IScaObjectIdentifierVisual.h"
#include "visual/Node.h"
#include "visual/LinkVisual.h"
#include "common/IScaObjectFile.h"
#include "common/IScaObjectTextBlock.h"
#include "common/IScaObjectDirectory.h"
#include "common/IScaObjectSymbol.h"
#include "common/IScaObjectLine.h"
#include "common/IScaObjectIdentifier.h"

ScaObjectConverter::ScaObjectConverter()
{

}

ScaObjectConverter::~ScaObjectConverter()
{
}

bool ScaObjectConverter::canConvert(Node *obj, IScaObject::IScaObjectType toType)
{
    switch(obj->getObjectType())
    {
    case IScaObject::IDENTIFIER:
        if (toType == IScaObject::TEXTBLOCK)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case IScaObject::TEXTBLOCK:
        if (toType == IScaObject::IDENTIFIER)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
        break;
    }
    return false;
}

IScaObjectTextBlockVisual *ScaObjectConverter::getTextBlockFromIdentifier(IScaObjectIdentifierVisual *obj, bool autoDel)
{
    IScaObjectIdentifier *objId = static_cast<IScaObjectIdentifier *>(obj->getObject());
    IScaObjectFile *objFile = new IScaObjectFile(objId->getFile());
    IScaObjectTextBlock *objBlock = new IScaObjectTextBlock(objFile, objId->getOffset(),
                                                    objId->getIdentifier().length(),
                                                    objId->getIdentifier());
    IScaObjectTextBlockVisual *new_obj = new IScaObjectTextBlockVisual(obj->pos(), objBlock);
    foreach(LinkVisual *link, obj->getLinks())
    {
        link->changeNode(obj, new_obj);
        new_obj->addLink(link);
        obj->disconnectLink(link);
    }
    if (autoDel)
        delete obj;
    return new_obj;
}

IScaObjectIdentifierVisual *ScaObjectConverter::getIdentifierFromBlock(IScaObjectTextBlockVisual *obj, bool autoDel)
{
    IScaObjectTextBlock *objBlock = static_cast<IScaObjectTextBlock *>(obj->getObject());
    IScaObjectFile *objFile = new IScaObjectFile(objBlock->getFile());
    IScaObjectIdentifier *objId = new IScaObjectIdentifier(objFile, objBlock->getOffset(),
                                                           objBlock->getText());

    IScaObjectIdentifierVisual *new_obj = new IScaObjectIdentifierVisual(obj->pos(), objId);
    foreach(LinkVisual *link, obj->getLinks())
    {
        link->changeNode(obj, new_obj);
        new_obj->addLink(link);
        obj->disconnectLink(link);
    }
    if (autoDel)
        delete obj;
    return new_obj;
}
