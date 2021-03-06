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
#include "NumericalConstants.h"
#include <QAbstractListModel>
#include <QMimeData>
#include <QList>
class Link;

class GraphModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit GraphModel(QObject *parent = 0);
    ~GraphModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRow(int id, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool removeObject(int id);
    bool removeObject(IScaObject *obj);

    int addObject(const QMimeData *mimeData);
    int addObject(IScaObject *object, int id = -1,  bool isShown = false);
    int replaceObject(IScaObject *object, int id);
    int getId(IScaObject *object);

    int connectObjects(int id1, int id2, int id = -1, QString annotation = QString());
    bool freeLink(int link);

    bool convert(int id, IScaObject::IScaObjectType toType);

    void editLinkAnnotation(int id);

    void clear();

    int getObjectIdByPath(const QString &path);
    QString getAnnotationByPath(const QString &path);
    IScaObject *getObjectByPath(const QString &path);
    IScaObject *getObjectById(const int &id);

    void addLinkTo(IScaObject *obj, int link);
    bool editAnnotation(int id);
    void setAnnotation(int id, const QString &annotation);
    void setFilePath(int id, const QString &path);

    bool hasIndex(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
private:
    static int s_nextID;
    QHash<int, IScaObject *> m_objects;
    QMap<int, bool> m_isShown;
}; // class GraphModel

Q_DECLARE_METATYPE( QList<int> )

#endif //_GraphModel_H_3675081C_AE2A_4F25_9543_C8883BE13A08_INCLUDED_
