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
#include "NumericalConstants.h"
#include <QDebug>
#include <QInputDialog>
#include <QVariant>
#include "common/IScaObject.h"
#include "common/Link.h"

GraphTableProxyModel::GraphTableProxyModel(QAbstractItemModel *source, QObject *parent) :
    QAbstractTableModel(parent),
    m_source(source)
{
}

GraphTableProxyModel::~GraphTableProxyModel()
{

}

int GraphTableProxyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_idMap.size();
}

int GraphTableProxyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return GRAPH_TABLE_PROXY_COLUMN_COUNT;
}

QVariant GraphTableProxyModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "[ProxyTableModel]: data(" << index.row() << ";" << role << ")";
    if (!index.isValid())
    {
        return QVariant();
    }
    int row = index.row();
    int column = index.column();
    switch (role)
    {
    case Qt::DisplayRole:
        {
            QVariant var =
                    m_source->data(m_source->index(m_idMap[row], column),
                                   rawObjectRole);
            IScaObject *obj = NULL;
            obj = qvariant_cast<IScaObject *>(var);
            if (obj == NULL)
            {
                obj = qvariant_cast<Link *>(var);
                if (obj == NULL)
                {
                    qDebug() << "[ProxyTableModel]: cant cast object";
                    return QVariant();
                }
            }
            switch (column)
            {
            case 0:
                return QVariant(obj->getTypeName());
            case 1:
                return QVariant(obj->getFile().fileName());
            case 2:
                return QVariant(obj->getFile().absoluteFilePath());
            case 3:
                return QVariant(obj->getAnnotation());
            case 4:
                return QVariant(obj->getContent());
            default:
                return QVariant();
            }

            break;
        }
    }

    return QVariant();
}

bool GraphTableProxyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    QVariant var = m_source->data(m_source->index(row, 0), objectIdListRole);
    QList<int> list = qvariant_cast<QList<int> >(var);
    qDebug() << "[ProxyTableModel]: update to " << list.size();

    if (!list.isEmpty())
    {
        int i = 0;
        beginInsertRows(QModelIndex(), 0, list.size() - 1);
        foreach (int id, list)
        {
            qDebug() << "[ProxyTableModel]: " << i << "->" << id;
            m_idMap[i++] = id;
        }
        endInsertRows();
    }
    return true;
}

void GraphTableProxyModel::updateMap()
{
    // TODO (LeoSko): right index missing when deleting element (no update available)
    removeRows(QModelIndex(), 0, rowCount());
    insertRows();
}

void GraphTableProxyModel::removeRows(QModelIndex parent, int begin, int end)
{
    if (!m_idMap.isEmpty())
    {
        beginRemoveRows(QModelIndex(), 0, m_idMap.size() - 1);
        qDebug() << "[ProxyTableModel]: clearing from 0 to " << m_idMap.size() - 1;
        m_idMap.clear();
        endRemoveRows();
    }
}
