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

IScaObject::IScaObject(IScaObjectType type) :
    m_type(type)
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

QList<Link *> IScaObject::getLinks() const
{
    return m_links;
}

void IScaObject::disconnectLink(Link *link)
{
    int index = m_links.indexOf(link);
    if (index > 0 && index < m_links.size())
    {
        m_links.removeAt(index);
    }
}

void IScaObject::addLink(Link *link)
{
    m_links.append(link);
}

void IScaObject::setLinks(const QList<Link *> &links)
{
    m_links = links;
}

QDebug operator<<(QDebug d, IScaObject &object)
{
    d << "IScaObject(type=" << object.getType() << ";cons=" << object.getLinks().size()
      << ";ann=" << object.getAnnotation() << ")";
    return d;
}


