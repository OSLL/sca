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
 * \file FilterDialog.cpp
 * \brief FilterDialog implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphView.h"
#include "FilterDialog.h"
#include "../MainWindow.h"
#include "../StringConstants.h"
#include "../common/IScaObject.h"

FilterDialog::FilterDialog(GraphFilter *filter, GraphScene* scene, QWidget *parent) :
    QDialog(parent),
    m_graphFilter(filter),
    m_scene(scene),
    m_ui(new Ui::FilterDialog)
{
    m_ui->setupUi(this);
    //Set current filter state to UI
    setValidRegExpState(m_graphFilter->getRegExp()->isValid());
    m_ui->annotationLineEdit->setText(m_graphFilter->getAnnotation());
    m_ui->fileNameLineEdit->setText(m_graphFilter->getFileName());
    m_ui->pathLineEdit->setText(m_graphFilter->getFilePath());
    m_ui->typeComboBox->setCurrentIndex((int)m_graphFilter->getObjType());
    m_ui->regexpLineEdit->setText(m_graphFilter->getRegExpPattern());

    //Connect changes of fields to graphFilter
    connect(m_ui->annotationLineEdit, SIGNAL(textEdited(QString)),
            m_graphFilter, SLOT(setAnnotation(QString)));
    connect(m_ui->fileNameLineEdit, SIGNAL(textEdited(QString)),
            m_graphFilter, SLOT(setFileName(QString)));
    connect(m_ui->pathLineEdit, SIGNAL(textEdited(QString)),
            m_graphFilter, SLOT(setFilePath(QString)));
    connect(m_ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
            m_graphFilter, SLOT(setObjType(int)));
    connect(m_ui->annotationLineEdit, SIGNAL(textEdited(QString)),
            m_ui->regexpRefreshButton, SLOT(click()));
    connect(m_ui->fileNameLineEdit, SIGNAL(textEdited(QString)),
            m_ui->regexpRefreshButton, SLOT(click()));
    connect(m_ui->pathLineEdit, SIGNAL(textEdited(QString)),
            m_ui->regexpRefreshButton, SLOT(click()));
    connect(m_ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
            m_ui->regexpRefreshButton, SLOT(click()));
    //Connect most advanced filter
    connect(m_ui->regexpRefreshButton, SIGNAL(clicked()),
            this, SLOT(refreshRegExp()));
    connect(m_ui->regexpLineEdit, SIGNAL(textEdited(QString)),
            m_graphFilter, SLOT(setRegExpPattern(QString)));
    //Connect to warn user that regexp is probably not valid in such case
    connect(m_graphFilter, SIGNAL(validRegExpState(bool)),
            this, SLOT(setValidRegExpState(bool)));
}

FilterDialog::~FilterDialog()
{
    delete m_ui;
}

void FilterDialog::reset()
{
    m_ui->regexpLineEdit->setText(DEFAULT_FILTER_REGEXP);
}

void FilterDialog::setValidRegExpState(bool arg)
{
    if (arg)
    {
        m_ui->regexpStateCheckBox->setText(VALID_REGEXP_STATE);
        m_ui->regexpStateCheckBox->setChecked(true);
        m_ui->regexpStateCheckBox->setIcon(QIcon());
    }
    else
    {
        m_ui->regexpStateCheckBox->setText(INVALID_REGEXP_STATE);
        m_ui->regexpStateCheckBox->setChecked(false);
        m_ui->regexpStateCheckBox->setIcon(QIcon::fromTheme("dialog-warning"));
    }
}

void FilterDialog::refreshRegExp()
{
    m_ui->regexpLineEdit->setText(m_graphFilter->getRegExpPattern());
}

void FilterDialog::on_regexpCheckBox_stateChanged(int arg1)
{
    m_ui->regexpLineEdit->setReadOnly(!arg1);
}

void FilterDialog::on_typeComboBox_currentIndexChanged(int index)
{
    bool isLink = (index == IScaObject::LINK);
    bool isDir = (index == IScaObject::DIRECTORY);
    //Allow to edit filepath only for non-link objects
    m_ui->pathLineEdit->setEnabled(!isLink);
    //Allow to edit filename for non-dir&&non-link objects
    m_ui->fileNameLineEdit->setEnabled(!isLink && !isDir);
}
