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
#include "MainWindow.h"
#include "StringConstants.h"

FilterDialog::FilterDialog(GraphFilter *filter, GraphScene* scene, QWidget *parent) :
    QDialog(parent),
    m_graphFilter(filter),
    m_scene(scene),
    m_ui(new Ui::FilterDialog)
{
    m_ui->setupUi(this);
    m_ui->regexpLineEdit->setText(m_graphFilter->getRegExpPattern());
}

FilterDialog::~FilterDialog()
{
    delete m_ui;
}

void FilterDialog::reset()
{
    m_ui->regexpLineEdit->setText(DEFAULT_FILTER_REGEXP);
}

void FilterDialog::on_regexpCheckBox_stateChanged(int arg1)
{
    m_ui->regexpLineEdit->setEnabled(arg1);
}

void FilterDialog::on_regexpLineEdit_textChanged(const QString &arg1)
{
    if (QRegExp(arg1).isValid())
    {
        m_graphFilter->setRegExpPattern(arg1);
        m_ui->regexpCheckBox->setIcon(QIcon());
        m_scene->refreshAll();
    }
    else
    {
        m_ui->regexpCheckBox->setIcon(QIcon::fromTheme("dialog-warning"));
    }
}
