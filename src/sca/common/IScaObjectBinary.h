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
 * \file IScaObjectBinary.h
 * \brief Header of IScaObjectBinary
 * \todo add comment here
 *
 * m_offset - number of bytes before binary block
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectBinary_H_7C395A44_235A_4C44_BFB1_9178EAA79A75_INCLUDED_
#define _IScaObjectBinary_H_7C395A44_235A_4C44_BFB1_9178EAA79A75_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include "common/IScaObject.h"
#include <QByteArray>
#include <QFile>

class IScaObjectBinary: public IScaObject
{
public:
  IScaObjectBinary();
  
  enum {Type = UserType + 3};


  QByteArray getBlock() const;
  void setBlock(const QByteArray &value);

  unsigned int getOffset() const;
  void setOffset(unsigned int offset);

  QFile *getFile() const;
  void setFile(QFile *file);

private:
  QByteArray m_block;
  unsigned int m_offset;
  QFile *m_file;
}; // class IScaObjectBinary


#endif //_IScaObjectBinary_H_7C395A44_235A_4C44_BFB1_9178EAA79A75_INCLUDED_
