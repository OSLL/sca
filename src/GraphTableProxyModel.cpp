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
 * \file GraphTableProxyModel.cpp
 * \brief GraphTableProxyModel implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphTableProxyModel.h"
#include <QDebug>

GraphTableProxyModel::GraphTableProxyModel(QAbstractItemModel *source, QObject *parent) :
    QAbstractProxyModel(parent)
{
    setSourceModel(source);
    connect(source, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(updateMap(QModelIndex, QModelIndex)));
}

GraphTableProxyModel::~GraphTableProxyModel()
{

}

int GraphTableProxyModel::rowCount(const QModelIndex &parent) const
{
    return sourceModel()->rowCount(parent);
}

int GraphTableProxyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QModelIndex GraphTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex ind = sourceModel()->index(m_idMap[row], column, parent);
    QVariant var = sourceModel()->data(ind, GraphModel::rawObjectRole);
    IScaObject *object = qvariant_cast<IScaObject *>(var);
    return createIndex(row, column, object);
}

QModelIndex GraphTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int row = m_idMap.key(sourceIndex.row());
    int column = sourceIndex.column();
    return index(row, column, sourceIndex.parent());
}

QModelIndex GraphTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    int row = proxyIndex.row();
    int column = proxyIndex.column();
    return sourceModel()->index(m_idMap[row], column, proxyIndex.parent());
}

QVariant GraphTableProxyModel::data(const QModelIndex &proxyIndex, int role) const
{
    if (m_idMap.isEmpty())
        return QVariant();
    int row = proxyIndex.row();
    if (row < 0 || row > rowCount(proxyIndex.parent()))
    {
        return QVariant();
    }
    if (!proxyIndex.isValid())
    {
        return QVariant();
    }
    if (!m_idMap.contains(row))
    {
        return QVariant();
    }
    switch (role)
    {
    case Qt::DisplayRole:
        {
            QVariant var = sourceModel()->data(mapToSource(proxyIndex),
                                               GraphModel::rawObjectRole);
            IScaObject *obj = qvariant_cast<IScaObject *>(var);
            if (obj == NULL)
            {
                qDebug() << "Cant cast object in GraphTableProxyModel";;
            }
            switch (proxyIndex.column())
            {
            case 0:
                return QVariant(obj->getTypeName());
            case 1:
                return QVariant(obj->getFile().fileName());
            case 2:
                return QVariant(obj->getFile().absoluteFilePath());
            case 3:
                return QVariant(obj->getAnnotation());
            default:
                return QVariant();
            }

            break;
        }
    default:
        return QVariant();
    }
    return QVariant();
}

QModelIndex GraphTableProxyModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

void GraphTableProxyModel::updateMap(QModelIndex from, QModelIndex to)
{
    int startRow = from.row();
    int endRow = to.row();
    for (int row = startRow; row < endRow; row++)
    {
        if (!m_idMap.contains(row))
        {
            //TODO (LeoSko) Stopped here
        }
    }
}

