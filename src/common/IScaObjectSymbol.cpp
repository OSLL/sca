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
 * \file IScaObjectSymbol.cpp
 * \brief IScaObjectSymbol implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "common/IScaObjectSymbol.h"


IScaObjectSymbol::IScaObjectSymbol():
    IScaObject(SYMBOL),
    m_symbol(0),
    m_offset(0),
    m_fileObject(NULL)
{
}

IScaObjectSymbol::IScaObjectSymbol(IScaObjectFile *file, unsigned int offset,
                                   const char &symbol):
    IScaObject(SYMBOL),
    m_symbol(symbol),
    m_offset(offset),
    m_fileObject(file)
{
    IScaObject::setFile(file->getFile());
}

IScaObjectSymbol::~IScaObjectSymbol()
{
    if (m_fileObject != NULL)
        delete m_fileObject;
}

IScaObjectFile *IScaObjectSymbol::file() const
{
    return m_fileObject;
}

void IScaObjectSymbol::setFile(const QFileInfo &file)
{
    m_file = file;
    m_fileObject->setFile(file);
}
char IScaObjectSymbol::getSymbol() const
{
    return m_symbol;
}

void IScaObjectSymbol::setSymbol(char symbol)
{
    m_symbol = symbol;
}
int IScaObjectSymbol::getOffset() const
{
    return m_offset;
}

void IScaObjectSymbol::setOffset(const int &offset)
{
    m_offset = offset;
}

QString IScaObjectSymbol::getContent() const
{
    return QString(m_symbol);
}





