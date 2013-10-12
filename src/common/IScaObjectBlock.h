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
 * \file IScaObjectText.h
 * \brief Header of IScaObjectText
 * \todo add comment here
 *
 * m_offset - number of symblos before text block
 * m_length - length of text-block in symbols
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectText_H_CF22847C_B31D_488E_9444_08DB68BF4607_INCLUDED_
#define _IScaObjectText_H_CF22847C_B31D_488E_9444_08DB68BF4607_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include <QString>
#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"

class IScaObjectBlock: public IScaObject
{
public:
    IScaObjectBlock();
    IScaObjectBlock(IScaObjectFile *file, IScaObjectType type = BINARYBLOCK,
                   unsigned int offset = 0, unsigned int length = 0);

    unsigned int getOffset() const;
    void setOffset(unsigned int offset);

    IScaObjectFile *getFile() const;
    void setFile(IScaObjectFile *file);

    unsigned int getLength() const;
    void setLength(unsigned int length);

private:
    unsigned int m_length;
    unsigned int m_offset;
    IScaObjectFile *m_file;

}; // class IScaObjectText
  

#endif //_IScaObjectText_H_CF22847C_B31D_488E_9444_08DB68BF4607_INCLUDED_
