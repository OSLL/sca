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
 * \file ContextMenu.h
 * \brief Header of ContextMenu
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _ContextMenu_H_4CE24F6B_C887_4206_BACE_13B4453125AB_INCLUDED_
#define _ContextMenu_H_4CE24F6B_C887_4206_BACE_13B4453125AB_INCLUDED_

#include <QMenu>

/*!
 * Class description. May use HTML formatting
 *
 */
class ContextMenu : public QMenu
{
public:
  ContextMenu(QWidget *parent = 0);
  ContextMenu(const QString &title, QWidget *parent = 0);
  ~ContextMenu();

  ContextMenu *addMenu(const QString &menu);
  QAction *addNewMenuEntry(const QString &name, bool enabled = true, QObject *receiver = 0, const char *slot = 0);
  void connectActionByName(const QString &name, QObject *receiver, const char *slot);
  QAction *getActionByName(const QString &name, const QString &submenuName = "");
  void connectActionByMenu(const QString &menu, const QString &actionName, QObject *receiver, const char *slot);

private:

}; // class ContextMenu
  

#endif //_ContextMenu_H_4CE24F6B_C887_4206_BACE_13B4453125AB_INCLUDED_

