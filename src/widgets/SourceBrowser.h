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
 * \file SourceBrowser.h
 * \brief Header of SourceBrowser
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _SourceBrowser_H_FFA4491B_B282_4A61_972A_1470A2944293_INCLUDED_
#define _SourceBrowser_H_FFA4491B_B282_4A61_972A_1470A2944293_INCLUDED_

#include <QTreeView>
#include <QSignalMapper>
#include <QFileInfo>

class IScaObject;

class SourceBrowser : public QTreeView
{
    Q_OBJECT
public:
    explicit SourceBrowser(QWidget *parent = 0);
    ~SourceBrowser();

    void setMenu(QMenu *menu);
    QMenu *getMenu() const;

    QFileInfo getCurrentFile();
private:
    QMenu *m_menu;
    QSignalMapper *m_signalMapper;

    void createContextMenu();

signals:
    void addToScene();
    void openBinaryFile();
    void openFile();
    void openFileAs(const QString &);
    void annotate();
    void contextMenuOnFile(bool);
    void runCommand(const QString &, const QString &);

public slots:
    void showContextMenu(const QPoint &pos);
    void goToObject(IScaObject *object);
    void goToPath(const QString &path);
    void runTool(const QString &tool);
    void goToCurrentPath();
    void expandByPath(const QString &path);
};

#endif //_SourceBrowser_H_FFA4491B_B282_4A61_972A_1470A2944293_INCLUDED_
