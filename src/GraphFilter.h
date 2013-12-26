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
 * \file GraphFilter.h
 * \brief Header of GraphFilter
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphFilter_H_17F0E77A_8435_483E_A4C3_DBB67209895D_INCLUDED_
#define _GraphFilter_H_17F0E77A_8435_483E_A4C3_DBB67209895D_INCLUDED_
#include <QSortFilterProxyModel>
#include "common/IScaObject.h"

/*!
 * Class description. May use HTML formatting
 *
 */

class GraphFilter: public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit GraphFilter(QAbstractItemModel *source, QObject *parent = 0);
    ~GraphFilter();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool filterAcceptsId(const QModelIndex &index) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    bool checkRegExp(IScaObject *object) const;

    QString getRegExpPattern() const;
    QRegExp *getRegExp() const;
    void setRegExp(const QRegExp &regExp);

    QString getFileName() const;
    QString getFilePath() const;
    IScaObject::IScaObjectType getObjType() const;
    QString getAnnotation() const;

public slots:
    void refreshRegExp();
    void setRegExpPattern(const QString &pattern);

    void setAnnotation(const QString &annotation);
    void setObjType(const IScaObject::IScaObjectType &objType);
    void setObjType(const int &objType);
    void setFilePath(const QString &filePath);
    void setFileName(const QString &fileName);
    void setContent(const QString &content);
signals:
    void filterChanged();
    void validRegExpState(bool);

private:
    QString m_fileName;
    QString m_filePath;
    QString m_content;
    IScaObject::IScaObjectType m_objType;
    QString m_annotation;
    QRegExp *m_regExp;
}; // class GraphFilter


#endif //_GraphFilter_H_17F0E77A_8435_483E_A4C3_DBB67209895D_INCLUDED_
