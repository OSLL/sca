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
 * \file GraphViewContextMenu.h
 * \brief Header of GraphViewContextMenu
 * \todo add comment here
 *
 * Class of GraphView's context menu
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphViewContextMenu_H_0A11A7DC_9AB1_49AA_9CF1_92E1139411AB_INCLUDED_
#define _GraphViewContextMenu_H_0A11A7DC_9AB1_49AA_9CF1_92E1139411AB_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 * Class for context menu in GraphView including
 *
 */

#include "widgets/ContextMenu.h"
#include "StringConstants.h"
class GraphViewContextMenu : public ContextMenu
{
public:
    explicit GraphViewContextMenu(QWidget *parent = 0);
    ~GraphViewContextMenu();

    void resetToDefault();
private:

}; // class GraphViewContextMenu
  

#endif //_GraphViewContextMenu_H_0A11A7DC_9AB1_49AA_9CF1_92E1139411AB_INCLUDED_

