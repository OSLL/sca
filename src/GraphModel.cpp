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
 * \file GraphModel.cpp
 * \brief GraphModel implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphModel.h"
#include "ScaMIMEDataProcessor.h"
#include "common/Link.h"
#include <QDebug>

quint64 GraphModel::s_nextID = 0;

GraphModel::GraphModel() :
    QAbstractListModel()
{

}

GraphModel::~GraphModel()
{

}

quint64 GraphModel::connectObjects(quint64 id1, quint64 id2)
{
    if (!m_objects.contains(id1) || !m_objects.contains(id2))
    {
        return NULL;
    }
    return connectObjects(m_objects[id1], m_objects[id2]);
}

quint64 GraphModel::connectObjects(IScaObject *source, IScaObject *dest)
{
    qDebug() << "Connecting " << *source << " with " << *dest;
    Link *res = new Link(source, dest);
    QModelIndex changedIndex = createIndex(s_nextID, 0);
    setData(changedIndex, QVariant::fromValue(res));

    return s_nextID++;
}

quint64 GraphModel::addObject(const QMimeData *mimeData)
{
    if (!mimeData->hasUrls())
    {
        return -1;
    }

    ScaMIMEDataProcessor processor(mimeData);
    IScaObject *object = processor.makeObject();
    return addObject(object);
}

quint64 GraphModel::addObject(IScaObject *object)
{
    qDebug() << "AddObject()";
    QModelIndex changedIndex = createIndex(s_nextID, 0);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return s_nextID++;
}

quint64 GraphModel::getId(IScaObject *object)
{
    return m_objects.key(object);
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "Data called!";
    switch (role)
    {
    case Qt::DecorationRole:
        {
            IScaObject *object = m_objects[index.row()];
            return QVariant::fromValue(object);
        }
    default:
        {
            return QVariant();
        }
    }

}

Qt::ItemFlags GraphModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool GraphModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    int removed = m_objects.remove(row);
    qDebug() << "Removed: ID = " << row;
    endRemoveRows();

    return true;
}

bool GraphModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!m_objects.contains(row))
    {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        m_objects.remove(row + i);
    }
    endRemoveRows();
    return true;
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "Objects: " << m_objects.size();
    return m_objects.size();
}

bool GraphModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isNull())
        return false;
    if (index.row() < 0)
        return false;
    switch (role)
    {
        case Qt::DecorationRole:
        {
            qDebug() << "Added element #" << s_nextID;
            IScaObject *object = NULL;
            object = qvariant_cast<IScaObject *>(value);
            if (object == NULL)
            {
                object = qvariant_cast<Link *>(value);
                if (object == NULL)
                {
                    qDebug() << "Can\'t cast object!";
                    return false;
                }
            }
            m_objects.insert(index.row(), object);
            emit dataChanged(index, index);
            return true;
        }
        default:
        {
            return false;
            break;
        }
    }
}

//Returns true if item existed
bool GraphModel::removeItemByIndex(quint64 id)
{
    return removeRow(id, QModelIndex());
}

bool GraphModel::removeItem(IScaObject *obj)
{
    return removeItemByIndex(m_objects.key(obj));
}
