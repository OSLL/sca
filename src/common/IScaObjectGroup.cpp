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
 *
 * \file IScaObjectGroup.cpp
 * \brief IScaObjectGroup implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "IScaObjectGroup.h"

IScaObjectGroup::IScaObjectGroup() :
    IScaObject(GROUP)
{
}

IScaObjectGroup::IScaObjectGroup(const QList<int> &objects,
                                 const QStringList &fileNames,
                                 const QStringList &paths,
                                 const QStringList &annotations,
                                 const QStringList &content) :
    IScaObject(GROUP),
    m_objects(objects)
{
    m_fileNames = fileNames;
    m_paths = paths;
    m_annotations = annotations;
    m_contet = content;
}

QStringList IScaObjectGroup::getContets() const
{
    return m_contet;
}

void IScaObjectGroup::setContets(const QStringList &value)
{
    m_contet = value;
}

IScaObjectGroup::~IScaObjectGroup()
{
}

QList<int> IScaObjectGroup::getObjects() const
{
    return m_objects;
}

QString IScaObjectGroup::getName() const
{
    return m_name;
}

void IScaObjectGroup::setName(const QString &name)
{
    m_name = name;
}

QString IScaObjectGroup::getContent() const
{
    return m_name;
}

void IScaObjectGroup::addObject(int id)
{
    m_objects.push_back(id);
}

void IScaObjectGroup::removeObject(int id)
{
    m_objects.removeOne(id);
}

QString IScaObjectGroup::getInfo(const QString &pattern) const
{

    QString fileNames = m_name;
    foreach(QString str, m_fileNames)
    {
        fileNames += str;
    }
    QString paths;
    foreach(QString str, m_paths)
    {
        paths += str;
    }
    QString annotations;
    foreach(QString str, m_annotations)
    {
        annotations += str;
    }
    QString content;
    foreach(QString str, m_contet)
    {
        content += str;
    }

    return  pattern
            .arg(m_type)
            .arg(fileNames)
            .arg(paths)
            .arg(annotations)
            .arg(content);
}

QStringList IScaObjectGroup::getFileNames() const
{
    return m_fileNames;
}

void IScaObjectGroup::setFileNames(const QStringList &value)
{
    m_fileNames = value;
}

QStringList IScaObjectGroup::getPaths() const
{
    return m_paths;
}

void IScaObjectGroup::setPaths(const QStringList &value)
{
    m_paths = value;
}

QStringList IScaObjectGroup::getAnnotations() const
{
    return m_annotations;
}

void IScaObjectGroup::setAnnotations(const QStringList &value)
{
    m_annotations = value;
}
