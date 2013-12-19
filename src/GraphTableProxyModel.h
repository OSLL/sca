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
 * \file GraphTableProxyModel.h
 * \brief Header of GraphTableProxyModel
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphTableProxyModel_H_E4E7A8A9_534E_4D70_83B5_DB38BEAFD0AD_INCLUDED_
#define _GraphTableProxyModel_H_E4E7A8A9_534E_4D70_83B5_DB38BEAFD0AD_INCLUDED_
#include <QAbstractProxyModel>
#include <GraphModel.h>
/*!
 * Class description. May use HTML formatting
 *
 */
class GraphTableProxyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GraphTableProxyModel(QAbstractItemModel *source, QObject *parent);
    ~GraphTableProxyModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int row = 0, int count = 0, const QModelIndex &parent = QModelIndex());
private:
    QMap<int, int> m_idMap;
    QAbstractItemModel *m_source;
public slots:
    void updateMap();
    void removeRows(QModelIndex parent, int begin, int end);
}; // class GraphTableProxyModel


#endif //_GraphTableProxyModel_H_E4E7A8A9_534E_4D70_83B5_DB38BEAFD0AD_INCLUDED_
