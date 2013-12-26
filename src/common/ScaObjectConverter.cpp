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
#include "GraphModel.h"

ScaObjectConverter::ScaObjectConverter()
{

}

ScaObjectConverter::~ScaObjectConverter()
{
}

bool ScaObjectConverter::canConvert(IScaObject *obj, IScaObject::IScaObjectType toType)
{
    return canConvert(obj->getType(), toType);
}

bool ScaObjectConverter::canConvert(IScaObject::IScaObjectType fromType, IScaObject::IScaObjectType toType)
{
    switch (fromType)
    {
    case IScaObject::IDENTIFIER:
        if (toType == IScaObject::TEXTBLOCK)
        {
            return true;
        }
        break;
    case IScaObject::TEXTBLOCK:
        if (toType == IScaObject::IDENTIFIER)
        {
            return true;
        }
        break;
    default:
        return false;
    }

    return false;
}


IScaObject *ScaObjectConverter::convert(IScaObject *obj, IScaObject::IScaObjectType toType)
{
    if (!canConvert(obj->getType(), toType))
    {
        return NULL;
    }
    switch (obj->getType())
    {
        case IScaObject::IDENTIFIER:
        {
            IScaObjectIdentifier *object = static_cast<IScaObjectIdentifier *>(obj);
            switch (toType)
            {
                case IScaObject::TEXTBLOCK:
                    return makeTextBlockFromIdentifier(object);
                default:
                    //Conversion can't be done
                    return NULL;
            }
        }
        case IScaObject::TEXTBLOCK:
        {
            IScaObjectTextBlock *object = static_cast<IScaObjectTextBlock *>(obj);
            switch (toType)
            {
                case IScaObject::IDENTIFIER:
                    return makeIdentifierFromBlock(object);
                default:
                    //Conversion can't be done
                    return NULL;
            }
        }
        default:
            //Conversion can't be done
            return NULL;
    }
}

IScaObjectTextBlock *ScaObjectConverter::makeTextBlockFromIdentifier(IScaObjectIdentifier *obj, bool autoDel)
{
    IScaObjectFile *file = new IScaObjectFile(obj->getFile());
    int offset = obj->getOffset();
    int endOffset = obj->getEndOffset();
    QString text = obj->getIdentifier();
    QList<int> links = obj->getLinks();

    IScaObjectTextBlock *textBlock = new IScaObjectTextBlock(file, offset, endOffset, text.size(), text);
    textBlock->setLinks(links);
    if (autoDel)
    {
        delete obj;
    }
    return textBlock;
}

IScaObjectIdentifier *ScaObjectConverter::makeIdentifierFromBlock(IScaObjectTextBlock *obj, bool autoDel)
{
    IScaObjectFile *file = new IScaObjectFile(obj->getFile());
    int offset = obj->getOffset();
    int endOffset = obj->getEndOffset();
    QString text = obj->getText();
    QList<int> links = obj->getLinks();

    IScaObjectIdentifier *identifier = new IScaObjectIdentifier(file, offset, endOffset, text);
    identifier->setLinks(links);
    if (autoDel)
    {
        delete obj;
    }
    return identifier;
}
