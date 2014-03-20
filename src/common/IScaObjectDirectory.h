/*
 * Copyright 2013  Nikita Razdobreev  exzo0mex@gmail.com

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
 * \file IScaObjectDirectory.h
 * \brief Header of IScaObjectDirectory
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectDirectory_H_C93082E1_57F6_4DAA_AA3F_3476C8A234B4_INCLUDED_
#define _IScaObjectDirectory_H_C93082E1_57F6_4DAA_AA3F_3476C8A234B4_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
#include "IScaObject.h"
#include <QFileInfo>

class IScaObjectDirectory: public IScaObject
{
public:

    IScaObjectDirectory();
    IScaObjectDirectory(const QFileInfo &fileInfo);

    QFileInfo getFile() const;
    void setFile(const QString &filePath);
    void setFile(const QFileInfo &file);
private:

}; // class IScaObjectDirectory


#endif //_IScaObjectDirectory_H_C93082E1_57F6_4DAA_AA3F_3476C8A234B4_INCLUDED_
