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
 * \file SourceBrowserMenu.cpp
 * \brief SourceBrowserMenu implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "SourceBrowserMenu.h"

#include <QMessageBox>
#include <QAction>
#include <QDebug>

SourceBrowserMenu::SourceBrowserMenu(QWidget *parent) :
    QMenu(parent)
{
    addAction(OPEN_IN_TEXT_VIEWER);
    m_openTextAs = addMenu(OPEN_IN_TEXT_VIEWER_AS);
    addAction(OPEN_IN_BINARY_VIEWER);

    m_openTextAs->addAction(UTF8);
    m_openTextAs->addAction(CP866);
    m_openTextAs->addAction(ISO885915);
}

SourceBrowserMenu::~SourceBrowserMenu()
{
    foreach(QAction *act, actions())
    {
        act->deleteLater();
    }
}

QAction *SourceBrowserMenu::addNewMenuEntry(const QString &name, bool enabled, QObject *receiver, const char *slot)
{
    QAction *act = QMenu::addAction(name, receiver, slot);
    act->setEnabled(enabled);
    return act;
}


void SourceBrowserMenu::connectActionByName(const QString &name, QObject *receiver, const char *slot)
{
    if (name.isEmpty() || receiver == NULL || slot == NULL)
    {
        qDebug() << "Error in params in connectActionByName:"
                 << "\nobject: " << this
                 << "name: " << name
                 << "\nreceiver: " << receiver
                 << "\nslot: " << slot;
        return;
    }
    QAction *action = getActionByName(name);
    if (action == NULL)
    {
        qDebug() << "Can\'t find action for name: " << name
                 << " while connecting to " << receiver << slot;
        return;
    }
    connect(action, SIGNAL(triggered()), receiver, slot);
}

QAction *SourceBrowserMenu::getActionByName(const QString &name, const QString &submenuName)
{
    QList<QAction *> acts;
    if (submenuName == OPEN_IN_TEXT_VIEWER_AS)
    {
        QMenu *submenu =  m_openTextAs;
        if(submenu == NULL)
        {
            return 0;
        }

        acts = submenu->actions();
    }
    else
    {
        acts = actions();
    }

    foreach(QAction *action, acts)
    {
        if (action->text() == name)
            return action;
    }
    return 0;
}

void SourceBrowserMenu::connectActionByMenu(const QString &menuName, const QString &actionName, QObject *receiver, const char *slot)
{

    if (menuName.isEmpty() || actionName.isEmpty() || receiver == NULL || slot == NULL)
    {
        qDebug() << "Error in params in connectActionByName:"
                 << "\nobject: " << this
                 << "\nmenu: " << menuName
                 << "name: " << actionName
                 << "\nreceiver: " << receiver
                 << "\nslot: " << slot;
        return;
    }

    QAction *menu = getActionByName(actionName, menuName);
    if (menu == NULL)
    {
        qDebug() << "Can\'t find action for name: " << actionName
                 << " in submenu: " << menuName
                 << " while connecting to " << receiver << slot;
        return;
    }
    connect(menu, SIGNAL(triggered()), receiver, slot);
}
