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
#include "common/IScaObject.h"
#include <QTextDocument>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QMimeData>
#include <QDebug>

SourceBrowser::SourceBrowser(QWidget *parent) :
    QTreeView(parent)
{
    createContextMenu();
}

SourceBrowser::~SourceBrowser()
{
    if (m_menu != NULL)
    {
        delete m_menu;
    }
    if (m_signalMapper != NULL)
    {
        delete m_signalMapper;
    }
}

void SourceBrowser::setMenu(QMenu *menu)
{
    qDebug() << "Menu changed" << endl;
    m_menu->deleteLater();
    m_menu = menu;
}

QMenu *SourceBrowser::getMenu() const
{
    return m_menu;
}

QFileInfo SourceBrowser::getCurrentFile()
{
    QFileSystemModel *fileModel = dynamic_cast<QFileSystemModel *>(this->model());
    if (fileModel == NULL)
    {
        return QFileInfo();
    }
    QFileInfo currentFile = fileModel->fileInfo(this->currentIndex());
    return currentFile;
}

void SourceBrowser::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = viewport()->mapToGlobal(pos);
    if(!indexAt(pos).isValid())
    {
        return;
    }

    //Get current item selected and check if it is file
    QFileInfo currentFile = getCurrentFile();
    emit contextMenuOnFile(currentFile.isFile());

    m_menu->exec(globalPos);
}

void SourceBrowser::goToObject(IScaObject *object)
{
    QString path = object->getFile().absoluteFilePath();
    if (path.isEmpty())
    {
        return;
    }
    QFileSystemModel *m = static_cast<QFileSystemModel *>(model());
    QModelIndex index = m->index(path);
    scrollTo(index, QAbstractItemView::PositionAtCenter);
    selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
}

void SourceBrowser::runTool(const QString &tool)
{
    if(!hasFocus())
    {
        return;
    }

    QFileInfo currentFile = getCurrentFile();

    QString command(tool);
    command.replace(QString("%f"), currentFile.filePath());
    emit runCommand(command);
}


void SourceBrowser::createContextMenu()
{
    m_menu = new QMenu(this);
    QAction *annotateAction   = m_menu->addAction(ANNOTATE_OBJECT);
    QAction *openInTextAction = m_menu->addAction(OPEN_IN_TEXT_VIEWER);
    QMenu *openTextAsMenu     = m_menu->addMenu(OPEN_IN_TEXT_VIEWER_AS);
    QAction *openInHexAction  = m_menu->addAction(OPEN_IN_BINARY_VIEWER);

    QAction *openAsUtf8Action  = openTextAsMenu->addAction(UTF8);
    QAction *openAsCp866Action = openTextAsMenu->addAction(CP866);
    QAction *openAsIsoAction   = openTextAsMenu->addAction(ISO885915);

    connect(openInTextAction, SIGNAL(triggered()),
            this, SIGNAL(openFile()));
    connect(openInHexAction, SIGNAL(triggered()),
            this, SIGNAL(openBinaryFile()));
    connect(annotateAction, SIGNAL(triggered()),
            this, SIGNAL(annotate()));

    m_signalMapper = new QSignalMapper (this);
    connect(openAsUtf8Action, SIGNAL(triggered()),
            m_signalMapper, SLOT(map()));
    connect(openAsCp866Action, SIGNAL(triggered()),
            m_signalMapper, SLOT(map()));
    connect(openAsIsoAction, SIGNAL(triggered()),
            m_signalMapper, SLOT(map()));

    m_signalMapper->setMapping(openAsUtf8Action, UTF8);
    m_signalMapper->setMapping(openAsCp866Action, CP866);
    m_signalMapper->setMapping(openAsIsoAction, ISO885915);

    connect(m_signalMapper, SIGNAL(mapped(QString)),
            this, SIGNAL(openFileAs(QString)));

    connect(this, SIGNAL(contextMenuOnFile(bool)),
            openInTextAction, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(contextMenuOnFile(bool)),
            openTextAsMenu, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(contextMenuOnFile(bool)),
            openInHexAction, SLOT(setEnabled(bool)));
}
