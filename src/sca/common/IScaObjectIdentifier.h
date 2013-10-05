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
 * \file IScaObjectIdintifier.h
 * \brief Header of IScaObjectIdintifier
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectIdintifier_H_BED47E9D_E7B3_45CB_A44B_729F32858DED_INCLUDED_
#define _IScaObjectIdintifier_H_BED47E9D_E7B3_45CB_A44B_729F32858DED_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"

class IScaObjectIdentifier: public IScaObject
{
public:
  IScaObjectIdentifier();
  IScaObjectIdentifier(IScaObjectFile *file, unsigned int offset, QString identifier);

  unsigned int offset() const;
  void setOffset(unsigned int offset);

  QString getIdintifier() const;
  void setIdintifier(const QString &value);

  IScaObjectFile *file() const;
  void setFile(IScaObjectFile *file);

private:
  unsigned int m_offset;
  QString m_identifier;
  IScaObjectFile *m_file;
}; // class IScaObjectIdintifier
  

#endif //_IScaObjectIdintifier_H_BED47E9D_E7B3_45CB_A44B_729F32858DED_INCLUDED_
