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
 * \file SourceBrowserMenu.h
 * \brief Header of SourceBrowserMenu
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _SourceBrowserMenu_H_D7F176A0_5C10_4475_8099_F81969769D30_INCLUDED_
#define _SourceBrowserMenu_H_D7F176A0_5C10_4475_8099_F81969769D30_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 * Class for storing actions for context menu in
 * SourceBrowser class
 *
 */

#include <QMenu>
#include "StringConstants.h"

class SourceBrowserMenu : public QMenu
{
public:
    explicit SourceBrowserMenu(QWidget *parent = 0);
    ~SourceBrowserMenu();

    QAction *addNewMenuEntry(const QString &name, bool enabled = true, QObject *receiver = 0, const char *slot = 0);
    void connectActionByName(const QString &name, QObject *receiver, const char *slot);
    QAction *getActionByName(const QString &name, const QString &submenuName = "");
    void connectActionByMenu(const QString &menu, const QString &actionName, QObject *receiver, const char *slot);

private:
    QMenu *m_openTextAs;
}; // class SourceBrowserMenu


#endif //_SourceBrowserMenu_H_D7F176A0_5C10_4475_8099_F81969769D30_INCLUDED_

