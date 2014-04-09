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
 *
 * \file IScaObject.cpp
 * \brief IScaObject implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObject.h"
#include <QDebug>

IScaObject::IScaObject(IScaObjectType type, QFileInfo file) :
    m_type(type),
    m_file(file)
{
    m_file.makeAbsolute();
}

IScaObject::~IScaObject()
{
}

IScaObject::IScaObjectType IScaObject::getType() const
{
    return m_type;
}

QString IScaObject::getTypeName() const
{
    // TODO (LeoSko) Make a static container (Map) for these strings
    switch (m_type)
    {
    case OBJECT:
        return SCA_OBJECT;
    case DIRECTORY:
        return SCA_DIRECTORY;
    case FILE:
        return SCA_FILE;
    case IDENTIFIER:
        return SCA_IDENTIFIER;
    case TEXTBLOCK:
        return SCA_TEXTBLOCK;
    case BINARYBLOCK:
        return SCA_BINARYBLOCK;
    case LINE:
        return SCA_LINE;
    case SYMBOL:
        return SCA_SYMBOL;
    case LINK:
        return SCA_LINK;
    case GROUP:
        return SCA_GROUP;
    default:
        return SCA_UNKNOWN;
    }
}

QString IScaObject::getAnnotation() const
{
    return m_annotation;
}

void IScaObject::setAnnotation(const QString &annotation)
{
    qDebug() << "[IScaObject]: new annotation: " << annotation;
    m_annotation = annotation;
}

QList<int> IScaObject::getLinks() const
{
    return m_links;
}

void IScaObject::disconnectLink(int link)
{
    m_links.removeOne(link);
}

void IScaObject::addLink(int link)
{
    m_links.append(link);
}

QFileInfo IScaObject::getFile() const
{
    return m_file;
}

QString IScaObject::getFileName() const
{
    return m_file.fileName();
}

QString IScaObject::getFilePath() const
{
    return m_file.absoluteFilePath();
}

void IScaObject::setFile(const QFileInfo &file)
{
    m_file = file;
}

QString IScaObject::getContent() const
{
    return QString();
}

void IScaObject::setLinks(const QList<int> &links)
{
    m_links = links;
}

QString IScaObject::getInfo(const QString &pattern) const
{
    return  pattern
            .arg(m_type)
            .arg(m_file.fileName())
            .arg(m_file.absoluteFilePath())
            .arg(m_annotation)
            .arg(getContent());
}

QDebug operator<<(QDebug d, IScaObject &object)
{
    d << "IScaObject(type=" << object.getType() << ";cons=" << object.getLinks().size()
      << ";ann=" << object.getAnnotation() << ")";
    return d;
}
