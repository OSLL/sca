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
 * \file IScaObjectIdentifier.cpp
 * \brief IScaObjectIdentifier implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObjectIdentifier.h"

IScaObjectIdentifier::IScaObjectIdentifier() :
    IScaObject(IDENTIFIER),
    m_offset(0),
    m_endOffset(0),
    m_identifier(QString("")),
    m_fileObject(NULL)
{
}

IScaObjectIdentifier::IScaObjectIdentifier(IScaObjectFile *file, int offset, int endOffset, QString identifier) :
    IScaObject(IDENTIFIER),
    m_offset(offset),
    m_endOffset(endOffset),
    m_identifier(identifier),
    m_fileObject(file)
{
    IScaObject::setFile(file->getFile());
}

IScaObjectIdentifier::~IScaObjectIdentifier()
{
    if (m_fileObject != NULL)
        delete m_fileObject;

}

QFileInfo IScaObjectIdentifier::getFile() const
{
    return m_file;
}

void IScaObjectIdentifier::setFile(const QFileInfo &file)
{
    m_file = file;
    m_fileObject->setFile(file.filePath());
}

QString IScaObjectIdentifier::getContent() const
{
    return m_identifier;
}

QString IScaObjectIdentifier::getIdentifier() const
{
    return m_identifier;
}

void IScaObjectIdentifier::setIdentifier(const QString &identifier)
{
    m_identifier = identifier;
}

int IScaObjectIdentifier::getOffset() const
{
    return m_offset;
}

void IScaObjectIdentifier::setOffset(const int &offset)
{
    m_offset = offset;
}
int IScaObjectIdentifier::getEndOffset() const
{
    return m_endOffset;
}

void IScaObjectIdentifier::setEndOffset(int endOffset)
{
    m_endOffset = endOffset;
}

