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

unsigned int GraphModel::s_nextID = 0;

GraphModel::GraphModel() :
    QAbstractListModel()
{

}

GraphModel::~GraphModel()
{

}

void GraphModel::addObject(QMimeData *mimeData)
{

    if (!mimeData->hasUrls())
    {
        return;
    }

    ScaMIMEDataProcessor processor(mimeData);
    IScaObject *object = processor.makeObject();
    m_objects.insert(s_nextID, object);

    QModelIndex changedIndex = index(s_nextID, 0);
    emit dataChanged(changedIndex, changedIndex);

    s_nextID++;
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    IScaObject *object = m_objects[index.row()];
    QVariant stored;
    stored.setValue(*object);

    return stored;
}

Qt::ItemFlags GraphModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool GraphModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool GraphModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    m_objects.remove(row);
    endRemoveRows();

    return true;
}

bool GraphModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return true;
}



int GraphModel::rowCount(const QModelIndex &parent) const
{
    return m_objects.size();
}
