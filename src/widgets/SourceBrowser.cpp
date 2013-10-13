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



#include "SourceBrowser.h"
#include <QTextDocument>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QFileSystemModel>
#include <QSignalMapper>
#include <QMessageBox>

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{
    m_menu = new SourceBrowserMenu(this);
    m_menu->connectActionByName(OPEN_IN_TEXT_VIEWER , this, SIGNAL(openFile()));
    m_menu->connectActionByName(OPEN_IN_BINARY_VIEWER, this, SIGNAL(openBinaryFile()));

    QSignalMapper* signalMapper = new QSignalMapper (this);
    m_menu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, UTF8, signalMapper, SLOT(map()));
    m_menu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, CP866, signalMapper, SLOT(map()));
    m_menu->connectActionByMenu(OPEN_IN_TEXT_VIEWER_AS, ISO885915, signalMapper, SLOT(map()));

    signalMapper->setMapping(m_menu->getActionByName(UTF8, OPEN_IN_TEXT_VIEWER_AS), UTF8);
    signalMapper->setMapping(m_menu->getActionByName(CP866, OPEN_IN_TEXT_VIEWER_AS), CP866);
    signalMapper->setMapping(m_menu->getActionByName(ISO885915, OPEN_IN_TEXT_VIEWER_AS), ISO885915);

    connect (signalMapper, SIGNAL(mapped(QString)), this, SIGNAL(openFileAs(QString))) ;
}

void SourceBrowser::setMenu(SourceBrowserMenu *_menu)
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
    if (fileModel != NULL)
    {
        QAction *action = m_menu->getActionByName(OPEN_IN_TEXT_VIEWER);
        QFileInfo currentFile = fileModel->fileInfo(this->currentIndex());
        //Enable only if it is file
        action->setEnabled(currentFile.isFile());
    }

    //Show menu and process input
    QAction *action = m_menu->exec(globalPos);
    if (!action)
    {
        return;
    }
}
