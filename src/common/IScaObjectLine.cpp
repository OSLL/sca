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
 * \file IScaObjectLine.cpp
 * \brief IScaObjectLine implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "common/IScaObjectLine.h"
#include "common/IScaObjectFile.h"
#include <QString>

IScaObjectLine::IScaObjectLine() :
    IScaObject(LINE),
    m_line(QString("")),
    m_lineNumber(0),
    m_file(NULL)
{
}

IScaObjectLine::IScaObjectLine(IScaObjectFile *file, const quint32 &lineNumber,
                               const QString &line) :
    IScaObject(LINE),
    m_line(line),
    m_lineNumber(lineNumber),
    m_file(file)
{
}

IScaObjectLine::~IScaObjectLine()
{
    if (m_file != NULL)
        delete m_file;
}

QString IScaObjectLine::getLine() const
{
    return m_line;
}

void IScaObjectLine::setLine(const QString &line)
{
    m_line = line;
}

QFileInfo IScaObjectLine::getFile() const
{
    return m_file->getFile();
}

void IScaObjectLine::setFile(const QFileInfo &file)
{
    m_file->setFile(file.filePath());
}

quint32 IScaObjectLine::lineNumber() const
{
    return m_lineNumber;
}

void IScaObjectLine::setLineNumber(const quint32 &lineNumber)
{
    m_lineNumber = lineNumber;
}



