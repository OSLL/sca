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
 * \file GraphLoader.cpp
 * \brief GraphLoader implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphLoader.h"
#include "ObjectCreator.h"

#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

GraphLoader::GraphLoader()
{

}

GraphLoader::~GraphLoader()
{
    m_query->clear();
    m_db.close();
    delete m_query;
}

void GraphLoader::loadGraph(QString path, GraphModel *model, GraphScene *scene)
{
    m_model = model;
    m_scene = scene;

    m_model->clear();

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if (!m_db.open())
    {
        qDebug() << m_query->lastError().text();
        return;
    }

    m_query = new QSqlQuery(m_db);

    //don't change order
    //Model must be loaded first
    loadNodes();
    loadNodesVisual();
    loadLinks();
}

void GraphLoader::loadNodes()
{
    if(!m_query->exec("SELECT * FROM node_table"))
    {
        qDebug() << m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    ObjectCreator creator;
    while (m_query->next())
    {
        int id             = m_query->value(rec.indexOf("id")).toInt();
        int type           = m_query->value(rec.indexOf("type")).toInt();
        int offset         = m_query->value(rec.indexOf("offset")).toInt();
        int length         = m_query->value(rec.indexOf("length")).toInt();
        QString path       = m_query->value(rec.indexOf("path")).toString();
        QString text       = m_query->value(rec.indexOf("text")).toString();
        QByteArray data    = m_query->value(rec.indexOf("data")).toByteArray();
        QString annotation = m_query->value(rec.indexOf("annotation")).toString();

        IScaObject *object = creator.createObject(type, offset, length, path, text, data, annotation);
        m_model->addObject(object , id);
    }
}

void GraphLoader::loadLinks()
{
    if(!m_query->exec("SELECT * FROM link_table"))
    {
        qDebug() << m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    while (m_query->next())
    {
        int id     = m_query->value(rec.indexOf("id")).toInt();
        int source = m_query->value(rec.indexOf("source")).toInt();
        int destin = m_query->value(rec.indexOf("destin")).toInt();
        QString annotation = m_query->value(rec.indexOf("annotation")).toString();
        m_model->connectObjects(source, destin, id, annotation);
    }
}

void GraphLoader::loadNodesVisual()
{
    if(!m_query->exec("SELECT * FROM nodeVisual_table"))
    {
        qDebug() << m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    while (m_query->next())
    {
        int id     = m_query->value(rec.indexOf("id")).toInt();
        qreal posX = m_query->value(rec.indexOf("posX")).toReal();
        qreal posY = m_query->value(rec.indexOf("posY")).toReal();

        Node *node = static_cast<Node *>(m_scene->getObjectById(id));
        node->setPos(QPointF(posX, posY));
    }
}
