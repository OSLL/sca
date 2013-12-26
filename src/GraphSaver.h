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
 * \file GraphSaver.h
 * \brief Header of GraphSaver
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphSaver_H_C2B0903A_DBC5_42FE_B319_4E6BD96D140F_INCLUDED_
#define _GraphSaver_H_C2B0903A_DBC5_42FE_B319_4E6BD96D140F_INCLUDED_
#include <QtSql/qsqldatabase.h>
#include <QtSql/QSqlQuery>

#include "common/IScaObject.h"
#include "common/Link.h"
#include "GraphModel.h"
#include "GraphScene.h"
/*!
 * Class description. May use HTML formatting
 *
 */
class GraphSaver
{
public:
  GraphSaver(QString path);
  ~GraphSaver();

  void insertNode(IScaObject *object, int id);

  void insertLink(Link *link, int id);
  void saveModel(GraphModel *model);
  void saveScene(GraphScene *scene);
  void insertNodeVisual(Node *node, int id);
  void insertLinkVisual(LinkVisual *link, int id);
private:
  QSqlDatabase m_db;
  QSqlQuery *m_query;
}; // class GraphSaver
  

#endif //_GraphSaver_H_C2B0903A_DBC5_42FE_B319_4E6BD96D140F_INCLUDED_
