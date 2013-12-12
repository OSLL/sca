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
 * \file FilterDialog.h
 * \brief Header of FilterDialog
 * \todo add comment here
 *
 * Widget that provides filtering objects in scene as far as searching them
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _FilterDialog_H_E11AD786_3F67_4A8B_8622_38B097BC9862_INCLUDED_
#define _FilterDialog_H_E11AD786_3F67_4A8B_8622_38B097BC9862_INCLUDED_

#include <QDialog>
#include "../GraphFilter.h"
#include "../GraphScene.h"
#include <ui_FilterDialog.h>
#include <QSignalMapper>

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(GraphFilter *filter, GraphScene *scene, QWidget *parent = 0);
    ~FilterDialog();

private:
    GraphFilter *m_graphFilter;
    GraphScene *m_scene;
    Ui::FilterDialog *m_ui;
    QSignalMapper *typeMapper;

signals:
    void filterChanged();

public slots:
    void reset();

private slots:
    //Use this slot to tell filter state of current regexp
    void setValidRegExpState(bool arg);
    void refreshRegExp();
    void on_regexpCheckBox_stateChanged(int arg1);
    void on_typeComboBox_currentIndexChanged(int index);
};

#endif // FILTERDIALOG_H
