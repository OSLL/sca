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
 * \file GraphLoader.h
 * \brief Header of GraphLoader
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphLoader_H_ECB49FE6_502D_4A31_9E84_0F486CF0F2DA_INCLUDED_
#define _GraphLoader_H_ECB49FE6_502D_4A31_9E84_0F486CF0F2DA_INCLUDED_
#include "GraphModel.h"
#include "GraphScene.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
/*!
   * Class description. May use HTML formatting
   *
   */
class GraphLoader
{
public:
    GraphLoader();
    GraphLoader(const QString &path);
    virtual ~GraphLoader();

    void loadGraph(GraphModel *model, GraphScene *scene);
    bool open(const QString &path);
    void close();
private:

    void loadNodes();
    void loadNodesVisual();
    void loadLinks();
    void loadLinksVisual();

    QSqlDatabase m_db;
    QSqlQuery *m_query;
    GraphModel *m_model;
    GraphScene *m_scene;
}; // class GraphLoader

#endif //_GraphLoader_H_ECB49FE6_502D_4A31_9E84_0F486CF0F2DA_INCLUDED_
