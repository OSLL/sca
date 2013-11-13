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
 * \file GraphViewContextMenu.cpp
 * \brief GraphViewContextMenu implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphViewContextMenu.h"

GraphViewContextMenu::GraphViewContextMenu(QWidget *parent) :
    ContextMenu(parent)
{
    addNewMenuEntry(CONNECT_NODES);
    addNewMenuEntry(DELETE_ITEMS);
    addSeparator();
    addNewMenuEntry(TO_TEXT_BLOCK);
    addNewMenuEntry(TO_IDENTIFIER);
    addSeparator();
    QAction *setSrcArrow = addNewMenuEntry(LEFT_ARROW);
    setSrcArrow->setCheckable(true);
    QAction *setDestArrow = addNewMenuEntry(RIGHT_ARROW);
    setDestArrow->setCheckable(true);
    addNewMenuEntry(EDIT_ANNOTATION);
    //addNewMenuEntry(TO_BINARY_BLOCK);
}

GraphViewContextMenu::~GraphViewContextMenu()
{
}
