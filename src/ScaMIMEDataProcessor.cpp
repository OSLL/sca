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
 * \file ScaMIMEDataProcessor.cpp
 * \brief ScaMIMEDataProcessor implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "ScaMIMEDataProcessor.h"
#include "NumericalConstants.h"
#include "StringConstants.h"
#include "common/IScaObjectTextBlock.h"
#include "common/IScaObjectBinaryBlock.h"
#include "common/IScaObjectDirectory.h"
#include "common/IScaObjectFile.h"
#include "common/IScaObjectIdentifier.h"
#include "common/IScaObjectLine.h"
#include "common/IScaObjectSymbol.h"
#include <QPointF>
#include <QMimeData>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>

ScaMIMEDataProcessor::ScaMIMEDataProcessor(const QMimeData *mime) :
    m_data(mime)
{
    m_filePath = m_data->urls().at(0).toLocalFile();
    m_fileInfo.setFile(m_filePath);
}

ScaMIMEDataProcessor::~ScaMIMEDataProcessor()
{

}

const QMimeData *ScaMIMEDataProcessor::getData() const
{
    return m_data;
}

void ScaMIMEDataProcessor::setData(const QMimeData *data)
{
    m_data = data;
}

IScaObject *ScaMIMEDataProcessor::makeObject()
{
    int offset     = m_data->property("position").toInt();
    int length     = m_data->property("length").toInt();
    int posInLine  = m_data->property("posInLine").toInt();
    int line       = m_data->property("line").toInt();
    int lineLength = m_data->property("lineLength").toInt();

    IScaObjectFile *objFile = new IScaObjectFile(m_fileInfo);

    qDebug() << m_data->data(BINARY_DATA).mid(0, 1);
    if(m_data->data(BINARY_DATA) != QByteArray())
    {
        QByteArray byteArray = m_data->data(BINARY_DATA);
        IScaObjectBinaryBlock *objBinary = new IScaObjectBinaryBlock(objFile, offset, length, byteArray);
        return objBinary;
    }

    if (m_data->hasText())   //IScaObjectTextBlock/Line/Symbol/Identifier
    {
        //Symbol?
        if (m_data->text().length() == 1)
        {
            char symbol = m_data->text().toAscii().at(0);
            IScaObjectSymbol *objSymbol = new IScaObjectSymbol(objFile, offset, symbol);
            return objSymbol;
        }

        //Line?
        if (lineLength == length
                && (posInLine == 0 || posInLine == lineLength))
        {
            IScaObjectLine *objLine = new IScaObjectLine(objFile, line, m_data->text());
            return objLine;
        }

        IScaObjectTextBlock *objBlock = new IScaObjectTextBlock(objFile, offset, length, m_data->text());
        return objBlock;
    }

    if (m_fileInfo.isFile())  //IScaObjectFile
    {
        return objFile;
    }
    if (m_fileInfo.isDir())   //IScaObjectDirectory
    {
        delete(objFile);
        IScaObjectDirectory *objDir = new IScaObjectDirectory(m_fileInfo);
        return objDir;
    }

    return new IScaObject();
}
