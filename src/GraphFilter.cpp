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


GraphFilter::GraphFilter(QObject *parent):
    QSortFilterProxyModel(parent)
{

}

GraphFilter::~GraphFilter()
{

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
    bool acceptable = object->getFile().absoluteFilePath().contains(filterRegExp());
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

