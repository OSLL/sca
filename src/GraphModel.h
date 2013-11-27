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
 * \file GraphModel.h
 * \brief Header of GraphModel
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphModel_H_3675081C_AE2A_4F25_9543_C8883BE13A08_INCLUDED_
#define _GraphModel_H_3675081C_AE2A_4F25_9543_C8883BE13A08_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include "common/IScaObject.h"
#include <QAbstractListModel>
#include <QMimeData>
class Link;

class GraphModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GraphModel();
    ~GraphModel();

    quint32 addObject(const QMimeData *mimeData);
    quint32 addObject(IScaObject *object);
    quint32 replaceObject(IScaObject *object, quint32 id);
    quint32 getId(IScaObject *object);
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRow(quint32 id, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DecorationRole);

    bool removeObject(quint32 id);
    bool removeObject(IScaObject *obj);

    bool freeLink(quint32 link);

    bool convert(quint32 id, IScaObject::IScaObjectType toType);

    quint32 connectObjects(quint32 id1, quint32 id2);

    void addLinkTo(IScaObject *obj, quint32 link);
    void editLinkAnnotation(quint32 id);

    void setAnnotation(quint32 id, QString annotation);

private:
    static quint32 s_nextID;
    QHash<quint32, IScaObject *> m_objects;
}; // class GraphModel


#endif //_GraphModel_H_3675081C_AE2A_4F25_9543_C8883BE13A08_INCLUDED_
