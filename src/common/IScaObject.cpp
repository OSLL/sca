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

#include "common/IScaObject.h"
#include <QDebug>

IScaObject::IScaObject(IScaObjectType type, QFileInfo file) :
    m_type(type),
    m_file(file)
{
}

IScaObject::~IScaObject()
{
}

IScaObject::IScaObjectType IScaObject::getType() const
{
    return m_type;
}

QString IScaObject::getAnnotation() const
{
    return m_annotation;
}

void IScaObject::setAnnotation(const QString &annotation)
{
    m_annotation = annotation;
}

QList<quint32> IScaObject::getLinks() const
{
    return m_links;
}

void IScaObject::disconnectLink(quint32 link)
{
    int index = m_links.indexOf(link);
    if (index != -1)
    {
        m_links.removeAt(index);
    }
}

void IScaObject::addLink(quint32 link)
{
    m_links.append(link);
}

QFileInfo IScaObject::getFile()
{
    return m_file;
}

void IScaObject::setFile(const QFileInfo &file)
{
    m_file = file;
}

QString IScaObject::getContent() const
{
    return QString();
}

void IScaObject::setLinks(const QList<quint32> &links)
{
    m_links = links;
}

QString IScaObject::getInfo(QString pattern) const
{
    QString result(pattern);
    return  result
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


