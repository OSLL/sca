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
 * \file ObjectCreator.cpp
 * \brief ObjectCreator implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "ObjectCreator.h"
#include "common/IScaObjectTextBlock.h"
#include "common/IScaObjectBinaryBlock.h"
#include "common/IScaObjectDirectory.h"
#include "common/IScaObjectFile.h"
#include "common/IScaObjectIdentifier.h"
#include "common/IScaObjectLine.h"
#include "common/IScaObjectSymbol.h"



ObjectCreator::ObjectCreator()
{

}

ObjectCreator::~ObjectCreator()
{

}

IScaObject *ObjectCreator::createObject(int type, int line,
                                        int offset, int endoffset,
                                        int length, QString path,
                                        QString text, QByteArray data,
                                        QString annotation)
{
    IScaObjectFile *objFile = new IScaObjectFile(QFileInfo(path));

    switch(type)
    {
        case IScaObject::BINARYBLOCK:
        {
            IScaObjectBinaryBlock *objBinary = new IScaObjectBinaryBlock(objFile, offset, length, data);
            objBinary->setAnnotation(annotation);

            return objBinary;
        }
        break;

        case IScaObject::IDENTIFIER:
        {
            IScaObjectIdentifier *objIdent = new IScaObjectIdentifier(objFile, offset, endoffset, text);
            objIdent->setAnnotation(annotation);

            return objIdent;
        }
        break;

        case IScaObject::SYMBOL:
        {
            char symbol = text.toAscii().at(0);
            IScaObjectSymbol *objSymbol = new IScaObjectSymbol(objFile, offset, symbol);
            objSymbol->setAnnotation(annotation);

            return objSymbol;
        }
        break;

        case IScaObject::LINE:
        {
            IScaObjectLine *objLine = new IScaObjectLine(objFile, line, offset, endoffset, text);
            objLine->setAnnotation(annotation);

            return objLine;
        }
        break;

        case IScaObject::TEXTBLOCK:
        {
            IScaObjectTextBlock *objBlock = new IScaObjectTextBlock(objFile, offset, endoffset, length, text);
            objBlock->setAnnotation(annotation);

            return objBlock;
        }
        break;

        case IScaObject::DIRECTORY:
        {
            IScaObjectDirectory *objDir = new IScaObjectDirectory(QFileInfo(path));
            objDir->setAnnotation(annotation);

            return objDir;
        }
        break;

        case IScaObject::FILE:
        {
            objFile->setAnnotation(annotation);

            return objFile;
        }
        break;

    }

    return new IScaObject();
}
