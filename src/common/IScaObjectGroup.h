/*
 * Copyright 2014  Leonid Skorospelov  leosko94@gmail.com
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
 * \file IScaObjectGroup.h
 * \brief Header of IScaObjectGroup
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObjectGroup_H_3D32BAC3_EECE_4F3E_A32B_E1F2E30FA1B9_INCLUDED_
#define _IScaObjectGroup_H_3D32BAC3_EECE_4F3E_A32B_E1F2E30FA1B9_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
#include "IScaObject.h"

class IScaObjectGroup : public IScaObject
{
public:
    IScaObjectGroup();
    IScaObjectGroup(const QList<int> &objects,
                    const QStringList &fileNames = QStringList(),
                    const QStringList &paths = QStringList(),
                    const QStringList &annotations = QStringList(),
                    const QStringList &contents = QStringList());
    ~IScaObjectGroup();
    
    QString getContent() const;

    void addObject(int id);
    void removeObject(int id);
    QList<int> getObjects() const;
    QString getName() const;
    void setName(const QString &name);

    QString getInfo(const QString &pattern) const;

    QStringList getAnnotations() const;
    void setAnnotations(const QStringList &value);

    QStringList getPaths() const;
    void setPaths(const QStringList &value);

    QStringList getFileNames() const;
    void setFileNames(const QStringList &value);

    QStringList getContents() const;
    void setContents(const QStringList &contents);

private:
    QList<int> m_objects;
    QList<QStringList> m_info;
    QString m_name;
    QStringList m_fileNames;
    QStringList m_paths;
    QStringList m_annotations;
    QStringList m_contents;
}; // class IScaObjectGroup


#endif //_IScaObjectGroup_H_3D32BAC3_EECE_4F3E_A32B_E1F2E30FA1B9_INCLUDED_

