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
 * \file IScaObjectSymbol.h
 * \brief Header of IScaObjectSymbol
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectSymbol_H_DAA42064_BA5A_435E_9221_B321E06E981C_INCLUDED_
#define _IScaObjectSymbol_H_DAA42064_BA5A_435E_9221_B321E06E981C_INCLUDED_

/*!
 * m_offset - number of bytes/symbols before symbol
 *
 */

#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"


class IScaObjectSymbol: public IScaObject
{
public:
    IScaObjectSymbol();
    IScaObjectSymbol(IScaObjectFile *file, unsigned int offset = 0,
                     const char &symbol = 0);
    ~IScaObjectSymbol();

    IScaObjectFile *file() const;
    void setFile(const QFileInfo &file);

    char getSymbol() const;
    void setSymbol(char symbol);

    quint32 getOffset() const;
    void setOffset(const quint32 &offset);

    QString getContent() const;

private:
    char m_symbol;
    quint32 m_offset;
    IScaObjectFile *m_fileObject;

}; // class IScaObjectSymbol


#endif //_IScaObjectSymbol_H_DAA42064_BA5A_435E_9221_B321E06E981C_INCLUDED_
