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
 * \file GraphFilter.cpp
 * \brief GraphFilter implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include <QDebug>
#include "GraphFilter.h"
#include "GraphModel.h"
#include "common/IScaObject.h"
#include "StringConstants.h"

GraphFilter::GraphFilter(QObject *parent):
    QSortFilterProxyModel(parent),
    m_fileName(QString("")),
    m_filePath(QString("")),
    m_objType(IScaObject::OBJECT),
    m_annotation(QString("")),
    m_regExp(new QRegExp(DEFAULT_FILTER_REGEXP, Qt::CaseInsensitive, QRegExp::Wildcard))
{
}

GraphFilter::~GraphFilter()
{
    delete m_regExp;
}

QVariant GraphFilter::data(const QModelIndex &index, int role) const
{
    if(role == Qt::ToolTipRole)
    {
        return QVariant(filterAcceptsId(index));
    }
    else if (role == Qt::DecorationRole)
    {
        return sourceModel()->data(index, role);
    }
    return QVariant();
}

bool GraphFilter::filterAcceptsId(const QModelIndex &index) const
{
    GraphModel *model = static_cast<GraphModel *>(sourceModel());
    if(model == NULL)
    {
        qDebug() << "This filter acceptebale only for GraphModel";
        return false;
    }
    QVariant var = sourceModel()->data(index, Qt::DecorationRole);
    IScaObject *object = qvariant_cast<IScaObject *>(var);
    if(object == NULL)
    {
        qDebug() << "Can't get object";
        return false;
    }

    bool acceptable = checkRegExp(object);

    qDebug() << "Path:" << object->getFile().absoluteFilePath();
    if(acceptable)
        qDebug() << "Object #" << index.internalId() << "acceptable for filter";
    else
        qDebug() << "Object #" << index.internalId() << "unacceptable for filter";

    return acceptable;
}

QModelIndex GraphFilter::index(int row, int column, const QModelIndex &parent) const
{
    return sourceModel()->index(row, column, parent);
}

bool GraphFilter::checkRegExp(IScaObject *object) const
{
    //If filter didn't change from default, nothing matches
    // TODO (LeoSko) this condition is bad on perfomance,
    // somehow maybe move it to check once a refresh needed
    if (m_regExp->pattern() == DEFAULT_FILTER_REGEXP)
    {
        return false;
    }

    //Check info of object to regexp
    QString info = object->getInfo();
    return m_regExp->exactMatch(info);
}

QString GraphFilter::getRegExpPattern() const
{
    return m_regExp->pattern();
}

QRegExp *GraphFilter::getRegExp() const
{
    return m_regExp;
}

void GraphFilter::setRegExpPattern(const QString &pattern)
{
    m_regExp->setPattern(pattern);
    emit validRegExpState(m_regExp->isValid());
    emit filterChanged();
}

void GraphFilter::refreshRegExp()
{
    QString pattern = OBJECTINFO_PATTERN;

    //Set object type filter
    if (m_objType == IScaObject::OBJECT)
        pattern = pattern.arg("*");
    else
        pattern = pattern.arg(QString::number(m_objType));

    //Set filename filter
    if (m_fileName.isEmpty())
        pattern = pattern.arg("*");
    else
        pattern = pattern.arg(QString("*") + m_fileName + QString("*"));

    //Set filepath filter
    if (m_filePath.isEmpty())
        pattern = pattern.arg("*");
    else
        pattern = pattern.arg(QString("*")+ m_filePath + QString("*"));

    //Set annotation filter
    if (m_annotation.isEmpty())
        pattern = pattern.arg("*");
    else
        pattern = pattern.arg(QString("*") + m_annotation + QString("*"));

    if (m_content.isEmpty())
        pattern = pattern.arg("*");
    else
        pattern = pattern.arg(QString("*") + m_content + QString("*"));

    m_regExp->setPattern(pattern);

    emit validRegExpState(m_regExp->isValid());
    emit filterChanged();
}

QString GraphFilter::getFileName() const
{
    return m_fileName;
}

void GraphFilter::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    refreshRegExp();
}

void GraphFilter::setContent(const QString &content)
{
    m_content = content;
    refreshRegExp();
}

QString GraphFilter::getFilePath() const
{
    return m_filePath;
}

void GraphFilter::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
    refreshRegExp();
}

IScaObject::IScaObjectType GraphFilter::getObjType() const
{
    return m_objType;
}

void GraphFilter::setObjType(const IScaObject::IScaObjectType &objType)
{
    m_objType = objType;
    refreshRegExp();
}

void GraphFilter::setObjType(const int &objType)
{
    IScaObject::IScaObjectType type = static_cast<IScaObject::IScaObjectType>(objType);
    setObjType(type);
}

QString GraphFilter::getAnnotation() const
{
    return m_annotation;
}

void GraphFilter::setAnnotation(const QString &annotation)
{
    m_annotation = annotation;
    refreshRegExp();
}

void GraphFilter::setRegExp(const QRegExp &regExp)
{
    m_regExp->setPattern(regExp.pattern());
}
