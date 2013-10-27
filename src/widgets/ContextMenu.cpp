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
 * \file ContextMenu.cpp
 * \brief ContextMenu implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "ContextMenu.h"
#include "StringConstants.h"
#include <QDebug>
#include <QList>

ContextMenu::ContextMenu(QWidget *parent) :
    QMenu(parent)
{

}

ContextMenu::ContextMenu(const QString &title, QWidget *parent) :
    QMenu(title, parent)
{

}

ContextMenu::~ContextMenu()
{
    foreach(QAction *act, actions())
    {
        act->deleteLater();
    }
}

ContextMenu *ContextMenu::addMenu(const QString &menu)
{
    return static_cast<ContextMenu *>(QMenu::addMenu(menu));
}

QAction *ContextMenu::addNewMenuEntry(const QString &name, bool enabled,
                                      QObject *receiver, const char *slot)
{
    QAction *act;
    if (receiver != NULL && slot != NULL)
    {
        act = QMenu::addAction(name, receiver, slot);
    }
    else
    {
        act = QMenu::addAction(name);
    }
    act->setParent(this);
    act->setEnabled(enabled);
    return act;
}

void ContextMenu::connectActionByName(const QString &name,
                                      QObject *receiver, const char *slot)
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

QAction *ContextMenu::getActionByName(const QString &name, const QString &submenuName)
{
    QList<QAction *> acts = findChildren<QAction *>();
    foreach(QAction *act, acts)
    {
        if (act->text() == name)
            return act;
    }
    return 0;
}

void ContextMenu::connectActionByMenu(const QString &menuName,
                                      const QString &actionName,
                                      QObject *receiver, const char *slot)
{
    if (menuName.isEmpty() || actionName.isEmpty()
            || receiver == NULL || slot == NULL)
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
