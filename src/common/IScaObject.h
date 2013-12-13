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
 * \file IScaObject.h
 * \brief Header of IScaObject
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _IScaObject_H_DEABB215_B876_4172_9900_18F7580370C7_INCLUDED_
#define _IScaObject_H_DEABB215_B876_4172_9900_18F7580370C7_INCLUDED_
/*!
 * Class description. May use HTML formatting
 *
 */

#include <QString>
#include <QVariant>
#include <QFileInfo>
#include "StringConstants.h"
class Link;

class IScaObject
{
public:
    enum IScaObjectType{
        OBJECT,
        DIRECTORY,
        FILE,
        IDENTIFIER,
        LINE,
        SYMBOL,
        TEXTBLOCK,
        BINARYBLOCK,
        LINK,
        GROUP
    };
    IScaObject(IScaObjectType type = OBJECT, QFileInfo file = QFileInfo());
    virtual ~IScaObject();

    IScaObjectType getType() const;

    QString getAnnotation() const;
    void setAnnotation(const QString &annotation);

    QList<quint32> getLinks() const;
    void setLinks(const QList<quint32> &links);

    QString getInfo(QString pattern = OBJECT_INFO_PATTERN) const;

    void disconnectLink(quint32 link);
    void addLink(quint32 link);

    friend QDebug operator<<(QDebug d, IScaObject &node);

    virtual QFileInfo getFile();
    virtual void setFile(const QFileInfo &file);

    virtual QString getContent() const;
private:
    QString m_annotation;

protected:
    QList<quint32> m_links;
    IScaObjectType m_type;
    QFileInfo m_file;

}; // class IScaObject

Q_DECLARE_METATYPE(IScaObject *)

#endif //_IScaObject_H_DEABB215_B876_4172_9900_18F7580370C7_INCLUDED_
