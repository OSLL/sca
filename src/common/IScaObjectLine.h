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
 * \file IScaObjectLine.h
 * \brief Header of IScaObjectLine
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectLine_H_7BBF2830_80B7_4603_A592_F0951541D29D_INCLUDED_
#define _IScaObjectLine_H_7BBF2830_80B7_4603_A592_F0951541D29D_INCLUDED_

/*!
 * m_offset - number of symbols before line
 *
 */

#include "common/IScaObject.h"
#include "common/IScaObjectFile.h"
#include <QString>

class IScaObjectLine: public IScaObject
{
public:
    IScaObjectLine();
    IScaObjectLine(IScaObjectFile *file, const int &lineNumber = 0,
                   const QString &line = "");
    ~IScaObjectLine();

    QString getLine() const;
    void setLine(const QString &line);

    QFileInfo getFile() const;
    void setFile(const QFileInfo &file);

    QString getContent() const;

    int lineNumber() const;
    void setLineNumber(const int &lineNumber);

private:
    QString m_line;
    int m_lineNumber;
    IScaObjectFile *m_fileObject;
}; // class IScaObjectLine


#endif //_IScaObjectLine_H_7BBF2830_80B7_4603_A592_F0951541D29D_INCLUDED_
