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

ScaMimeDataProcessor::ScaMimeDataProcessor(const QMimeData *mime) :
    m_data(mime)
{
    QString path;
    if (m_data->hasUrls())
    {
        path = m_data->urls().at(0).toLocalFile();
    }
    else
    {
        path = QString(m_data->data(FROM_PATH));
    }
    qDebug() << "[ScaMIMEDataProcessor]: filePath - " << path;
    //Q_ASSERT(!path.isEmpty());
    m_filePath = path;
    m_fileInfo.setFile(m_filePath);
}

ScaMimeDataProcessor::~ScaMimeDataProcessor()
{

}

const QMimeData *ScaMimeDataProcessor::getData() const
{
    return m_data;
}

void ScaMimeDataProcessor::setData(const QMimeData *data)
{
    m_data = data;
}

IScaObject *ScaMimeDataProcessor::makeObject()
{
    int offset     = m_data->data(POSITION).toInt();
    int length     = m_data->data(LENGHT).toInt();
    int posInLine  = m_data->data(POS_IN_LINE).toInt();
    int line       = m_data->data(LINE_NUMBER).toInt();
    int lineLength = m_data->data(LINE_LENGHT).toInt();
    int endOffset  = m_data->data(END_OFFSET).toInt();
    QString text = m_data->text();
    QString path = m_fileInfo.filePath();
    QByteArray data = m_data->data(BINARY_DATA);

    IScaObject::IScaObjectType type = IScaObject::FILE;

    if(!m_data->data(BINARY_DATA).isEmpty())
    {
        type = IScaObject::BINARYBLOCK;
    }
    else if (m_data->hasText())   //IScaObjectTextBlock/Line/Symbol/Identifier
    {
        if (m_data->text().length() == 1)
        {
            type = IScaObject::SYMBOL;
        }
        else if (lineLength == length
                && (posInLine == 0 || posInLine == lineLength))
        {
            type = IScaObject::LINE;
        }
        else
        {
            type = IScaObject::TEXTBLOCK;
        }
    }
    else if (m_fileInfo.isFile())  //IScaObjectFile
    {
        type = IScaObject::FILE;
    }
    else if (m_fileInfo.isDir())   //IScaObjectDirectory
    {
        type = IScaObject::DIRECTORY;
    }

    return ObjectCreator::createObject(type, line, offset, endOffset, length,
                                       path, text, data);
}
