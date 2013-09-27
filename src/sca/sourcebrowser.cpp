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
 * \file SourceBrowser.cpp
 * \brief SourceBrowser implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */



#include "sourcebrowser.h"

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{
    m_menu = new QMenu(this);
    QAction *open = m_menu->addAction("Open in Text Viewer");
    m_menu->addAction("Open in Binary Viewer")->setEnabled(false);
    m_menu->addAction("Add to scene")->setEnabled(false);
}

void SourceBrowser::setMenu(QMenu *_menu)
{
    m_menu->deleteLater();
    m_menu = _menu;
}

void SourceBrowser::ShowContextMenu(const QPoint &pos)
{
    //Move menu
    QPoint globalPos = viewport()->mapToGlobal(pos);

    //Get current item selected and check if it is file
    QFileSystemModel *fileModel = dynamic_cast<QFileSystemModel *>(this->model());
    if (fileModel)
    {
        if (!fileModel->fileInfo(this->currentIndex()).isFile())
        {
            m_menu->actions().at(0)->setEnabled(false);
        }
        else
        {
            m_menu->actions().at(0)->setEnabled(true);
        }
    }

    //Show menu and process input
    QAction *action = m_menu->exec(globalPos);
    if (!action)
    {
        return;
    }

    int index = m_menu->actions().indexOf(action);
    switch(index)
    {
    case 0: //"Open in Text Viewer"
        emit openFile();
        break;
    case 1: //"Open in Binary Viewer"
        emit openBinaryFile();
        break;
    case 2: //"Add to scene"
        emit addToScene();
        break;
    default:
        QMessageBox::information(this, "Wrong menu index", "Got wrong index:" + QString::number(index), QMessageBox::Ok);
        break;
    }
}
