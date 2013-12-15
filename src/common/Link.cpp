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
 *
 * \file Link.cpp
 * \brief Link implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "common/Link.h"
#include <QDebug>

Link::Link() :
    IScaObject(LINK),
    m_annotation(QString("")),
    m_objectFrom(0),
    m_objectTo(0)
{
}

Link::Link(int objectFrom, int objectTo) :
    IScaObject(LINK),
    m_annotation(QString("")),
    m_objectFrom(objectFrom),
    m_objectTo(objectTo)
{
}

Link::~Link()
{
}

int Link::getObjectTo() const
{
    return m_objectTo;
}

void Link::setObjectTo(int objectTo)
{
    m_objectTo = objectTo;
}

QString Link::getAnnotation() const
{
    return m_annotation;
}

void Link::setAnnotation(const QString &annotation)
{
    m_annotation = annotation;
}

QDebug operator<<(QDebug d, Link &link)
{
    d << "Link(" << link.getObjectFrom() << ";" << link.getObjectTo() << ";ann="
      << link.getAnnotation() << ")";
    return d;
}

int Link::getObjectFrom() const
{
    return m_objectFrom;
}

void Link::setObjectFrom(int objectFrom)
{
    m_objectFrom = objectFrom;
}
