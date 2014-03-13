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
 *
 * \file VisualObjectCreator.cpp
 * \brief VisualObjectCreator implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "ObjectVisualCreator.h"
#include <QDebug>


ObjectVisualCreator::ObjectVisualCreator()
{

}

ObjectVisualCreator::~ObjectVisualCreator()
{

}

IScaObjectGroupVisual *ObjectVisualCreator::createGroupVisual(IScaObject *object)
{
    IScaObjectGroup *groupObject = static_cast<IScaObjectGroup *>(object);
    IScaObjectGroupVisual *node = new IScaObjectGroupVisual(groupObject);
    return node;
}

IScaObjectFileVisual *ObjectVisualCreator::createFileVisual(IScaObject *object)
{
    IScaObjectFile *fileObject = static_cast<IScaObjectFile *>(object);
    IScaObjectFileVisual *node = new IScaObjectFileVisual(fileObject);
    return node;
}

IScaObjectSymbolVisual *ObjectVisualCreator::createSymbolVisual(IScaObject *object)
{
    IScaObjectSymbol *symbolObject = static_cast<IScaObjectSymbol *>(object);
    IScaObjectSymbolVisual *node = new IScaObjectSymbolVisual(symbolObject);
    return node;
}

IScaObjectLineVisual *ObjectVisualCreator::createLineVisual(IScaObject *object)
{
    IScaObjectLine *lineObject = static_cast<IScaObjectLine *>(object);
    IScaObjectLineVisual *node = new IScaObjectLineVisual(lineObject);
    return node;
}

IScaObjectBinaryBlockVisual *ObjectVisualCreator::createBinaryBlockVisual(IScaObject *object)
{
    IScaObjectBinaryBlock *binaryObject = static_cast<IScaObjectBinaryBlock *>(object);
    IScaObjectBinaryBlockVisual *node = new IScaObjectBinaryBlockVisual(binaryObject);
    return node;
}

IScaObjectIdentifierVisual *ObjectVisualCreator::createIdentifierVisual(IScaObject *object)
{
    IScaObjectIdentifier *identObject = static_cast<IScaObjectIdentifier *>(object);
    IScaObjectIdentifierVisual *node = new IScaObjectIdentifierVisual(identObject);
    return node;
}

IScaObjectDirectoryVisual *ObjectVisualCreator::createDirVisual(IScaObject *object)
{
    IScaObjectDirectory *dirObject = static_cast<IScaObjectDirectory *>(object);
    IScaObjectDirectoryVisual *node = new IScaObjectDirectoryVisual(dirObject);
    return node;
}

IScaObjectTextBlockVisual *ObjectVisualCreator::createTextBlockVisual(IScaObject *object)
{
    IScaObjectTextBlock *textObject = static_cast<IScaObjectTextBlock *>(object);
    IScaObjectTextBlockVisual *node = new IScaObjectTextBlockVisual(textObject);
    return node;
}

LinkVisual *ObjectVisualCreator::createLinkVisual(IScaObject *object)
{
    Link *link = NULL;
    link = static_cast<Link *>(object);
    if (link == NULL)
    {
        qDebug() << "[ObjectVisualCreater]: cant cast to Link";
        return NULL;
    }
    LinkVisual *linkVisual = new LinkVisual(link);
    return linkVisual;
}


ObjectVisual *ObjectVisualCreator::createObjectVisual(IScaObject *object)
{
    IScaObject::IScaObjectType type = object->getType();
    ObjectVisual *visObject = NULL;

    switch(type)
    {
        case IScaObject::FILE:
        {
            visObject = createFileVisual(object);
            break;
        }
        case IScaObject::DIRECTORY:
        {
            visObject = createDirVisual(object);
            break;
        }
        case IScaObject::TEXTBLOCK:
        {
            visObject = createTextBlockVisual(object);
            break;
        }
        case IScaObject::BINARYBLOCK:
        {
            visObject = createBinaryBlockVisual(object);
            break;
        }
        case IScaObject::LINE:
        {
            visObject = createLineVisual(object);
            break;
        }
        case IScaObject::IDENTIFIER:
        {
            visObject = createIdentifierVisual(object);
            break;
        }
        case IScaObject::SYMBOL:
        {
            visObject = createSymbolVisual(object);
            break;
        }
        case IScaObject::LINK:
        {
            visObject = createLinkVisual(object);
            break;
        }
        case IScaObject::GROUP:
        {
            visObject = createGroupVisual(object);
            break;
        }
        default:
        {
            qDebug() << "Unknown type of object trying to create on scene.";
            break;
        }
    }
    visObject->setAnnotation(object->getAnnotation());
    //qDebug() << "Successfully createed object to scene.";
    return visObject;
}
