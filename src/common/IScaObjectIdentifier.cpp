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

#include "common/IScaObjectIdentifier.h"

IScaObjectIdentifier::IScaObjectIdentifier() :
    IScaObject(IDENTIFIER),
    m_offset(0),
    m_identifier(QString("")),
    m_file(NULL)
{
}

IScaObjectIdentifier::IScaObjectIdentifier(IScaObjectFile *file, unsigned int offset, QString identifier) :
    IScaObject(IDENTIFIER),
    m_offset(offset),
    m_identifier(identifier),
    m_file(file)
{
}

IScaObjectIdentifier::~IScaObjectIdentifier()
{
    if (m_file != NULL)
        delete m_file;

}

IScaObjectFile *IScaObjectIdentifier::getFile() const
{
    return m_file;
}

void IScaObjectIdentifier::setFile(IScaObjectFile *file)
{
    m_file = file;
}

QString IScaObjectIdentifier::getIdentifier() const
{
    return m_identifier;
}

void IScaObjectIdentifier::setIdentifier(const QString &identifier)
{
    m_identifier = identifier;
}
quint64 IScaObjectIdentifier::offset() const
{
    return m_offset;
}

void IScaObjectIdentifier::setOffset(const quint64 &offset)
{
    m_offset = offset;
}
