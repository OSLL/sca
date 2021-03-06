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
 * \file IScaObjectBinaryBlock.h
 * \brief Header of IScaObjectBinaryBlock
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectBinaryBlock_H_F754FD25_47B9_464B_9178_653BB17B069C_INCLUDED_
#define _IScaObjectBinaryBlock_H_F754FD25_47B9_464B_9178_653BB17B069C_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
#include <QString>
#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"

class IScaObjectBinaryBlock: public IScaObject
{
public:
    IScaObjectBinaryBlock();
    IScaObjectBinaryBlock(IScaObjectFile *file, unsigned int offset,
                          unsigned int length, const QByteArray &data = QByteArray());
    ~IScaObjectBinaryBlock();

    unsigned int getOffset() const;
    void setOffset(unsigned int offset);

    QFileInfo getFile() const;
    void setFile(const QFileInfo &file);

    unsigned int getLength() const;
    void setLength(unsigned int length);

    QByteArray getData() const;
    void setData(const QByteArray &block);

    QString getReadableData() const;

    QString getContent() const;

private:
    int m_length;
    int m_offset;
    QByteArray m_data;
    IScaObjectFile *m_fileObject;

}; // class IScaObjectBinaryBlock
  

#endif //_IScaObjectBinaryBlock_H_F754FD25_47B9_464B_9178_653BB17B069C_INCLUDED_
