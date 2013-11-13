/*
 * Copyright 2013  Leonid Skorospelov  leosko94@gmail.com
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
 * \file Link.h
 * \brief Header of Link
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _Link_H_DCF3C0AC_DBF1_4D8D_B8BD_6E10F500FD33_INCLUDED_
#define _Link_H_DCF3C0AC_DBF1_4D8D_B8BD_6E10F500FD33_INCLUDED_

#include "common/IScaObject.h"

/*!
 * Class description. May use HTML formatting
 *
 */
class Link: public IScaObject
{
public:
    Link();
    Link(IScaObject *objectFrom, IScaObject *objectTo);
    ~Link();

    IScaObject *getObjectFrom() const;
    void setObjectFrom(IScaObject *objectFrom);

    IScaObject *getObjectTo() const;
    void setObjectTo(IScaObject *objectTo);

    QString getAnnotation() const;
    void setAnnotation(const QString &annotation);

private:
    QString m_annotation;
    IScaObject *m_objectFrom;
    IScaObject *m_objectTo;

}; // class Link
  

#endif //_Link_H_DCF3C0AC_DBF1_4D8D_B8BD_6E10F500FD33_INCLUDED_

