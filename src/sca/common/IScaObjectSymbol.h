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
 * m_offset - number of bytes before symbol
 *
 */

#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"

class IScaObjectSymbol: public IScaObject
{
public:
    IScaObjectSymbol();
    IScaObjectSymbol(IScaObjectFile *file, unsigned int offset, QChar symbol);

    QChar symbol() const;
    void setSymbol(const QChar &symbol);

    unsigned int offset() const;
    void setOffset(unsigned int offset);

    IScaObjectFile *file() const;
    void setFile(IScaObjectFile *file);

private:
    QChar m_symbol;
    unsigned int m_offset;
    IScaObjectFile *m_file;

}; // class IScaObjectSymbol


#endif //_IScaObjectSymbol_H_DAA42064_BA5A_435E_9221_B321E06E981C_INCLUDED_
