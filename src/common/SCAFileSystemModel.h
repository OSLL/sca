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
 * \file SCAFileSystemModel.h
 * \brief Header of SCAFileSystemModel
 * \todo add comment here
 *
 * QFileSystemModel subclass to provide additional column for annotations
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "QFileSystemModel"
#include "../GraphModel.h"
#include "../GraphFilter.h"

#ifndef _SCAFileSystemModel_H_6AC5502B_905E_4593_BFE2_5ABACC15BFEE_INCLUDED_
#define _SCAFileSystemModel_H_6AC5502B_905E_4593_BFE2_5ABACC15BFEE_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
class SCAFileSystemModel : public QFileSystemModel
{
public:
    explicit SCAFileSystemModel(GraphModel *model, QObject *object = NULL);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    ~SCAFileSystemModel();
private:
    GraphModel *m_graphModel;
}; // class SCAFileSystemModel


#endif //_SCAFileSystemModel_H_6AC5502B_905E_4593_BFE2_5ABACC15BFEE_INCLUDED_

