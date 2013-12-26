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
 * \file TableView.cpp
 * \brief TableView implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "TableView.h"
#include "../StringConstants.h"
#include <QDebug>

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
    m_headerMenu = new ContextMenu(this);
    m_headerMenu->addNewMenuEntry(OBJECT_TYPE)->setCheckable(true);
    m_headerMenu->addNewMenuEntry(OBJECT_NAME)->setCheckable(true);
    m_headerMenu->addNewMenuEntry(OBJECT_PATH)->setCheckable(true);
    m_headerMenu->addNewMenuEntry(OBJECT_ANNOTATION)->setCheckable(true);
    m_headerMenu->addNewMenuEntry(OBJECT_CONTENT)->setCheckable(true);
}

TableView::~TableView()
{

}

void TableView::ShowContextMenu(const QPoint &pos)
{
    QList<QAction *> acts = m_headerMenu->actions();
    int enabled = 0;
    for (int i = 0; i < acts.size(); i++)
    {
        acts.at(i)->setEnabled(true);
        acts.at(i)->setChecked(!this->isColumnHidden(i));
        enabled += !isColumnHidden(i);
    }
    //If we have one column left disable disabling of last column
    if (enabled == 1)
    {
        foreach(QAction *act, acts)
        {
            if (act->isChecked())
            {
                act->setEnabled(false);
                break;
            }
        }
    }
    QAction *act = m_headerMenu->exec(mapToGlobal(pos));
    int i = acts.indexOf(act);
    if (i != -1)
    {
        qDebug() << "[TableView]: Found proper action, #" << i;
        acts[i]->toggle();
        bool newState = acts[i]->isChecked();
        if (newState == true)
        {
            hideColumn(i);
        }
        else
        {
            showColumn(i);
        }
    }
}
