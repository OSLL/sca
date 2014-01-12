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
#include "StringConstants.h"

#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>



GraphLoader::GraphLoader()
{

}

GraphLoader::GraphLoader(const QString &path)
{
    open(path);
}

GraphLoader::~GraphLoader()
{
    m_query->clear();
    m_db.close();
    delete m_query;
}


bool GraphLoader::open(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "[GraphLoader]:" << m_db.lastError().text();
        return false;
    }
    m_query = new QSqlQuery(m_db);

    return true;
}

void GraphLoader::loadGraph(GraphModel *model, GraphScene *scene)
{
    if(!m_db.open())
    {
        qDebug() << "[GraphLoader]: Error: file does't open";
        return;
    }

    m_model = model;
    m_scene = scene;

    m_model->clear();

    //don't change this order
    loadNodes();
    loadNodesVisual();
    loadLinks();
    loadLinksVisual();
}

void GraphLoader::loadNodes()
{
    if(!m_query->exec(SQL_SELECT_NODE_TYPE_TABLES))
    {
        qDebug() << "[GraphLoader]:" <<  m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    ObjectCreator creator;
    while (m_query->next())
    {
        int id             = m_query->value(rec.indexOf("id")).toInt();
        int type           = m_query->value(rec.indexOf("type")).toInt();
        int line           = m_query->value(rec.indexOf("line")).toInt();
        int offset         = m_query->value(rec.indexOf("offset")).toInt();
        int endoffset      = m_query->value(rec.indexOf("endoffset")).toInt();
        int length         = m_query->value(rec.indexOf("length")).toInt();
        QString path       = m_query->value(rec.indexOf("path")).toString();
        QString text       = m_query->value(rec.indexOf("text")).toString();
        QByteArray data    = m_query->value(rec.indexOf("data")).toByteArray();
        QString annotation = m_query->value(rec.indexOf("annotation")).toString();
        bool isShown       = m_query->value(rec.indexOf("shown")).toBool();

        IScaObject *object = creator.createObject(type, line, offset, endoffset, length, path, text, data, annotation);
        m_model->addObject(object , id, isShown);
    }
}

void GraphLoader::loadLinks()
{
    if(!m_query->exec(SQL_SELECT_LINK_TABLE))
    {
        qDebug() << "[GraphLoader]:" << m_query->lastError().text();
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
    if(!m_query->exec(SQL_SELECT_NODEVISUAL_TABLE))
    {
        qDebug() << "[GraphLoader]:" << m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    while (m_query->next())
    {
        int id     = m_query->value(rec.indexOf("id")).toInt();
        qreal posX = m_query->value(rec.indexOf("posX")).toReal();
        qreal posY = m_query->value(rec.indexOf("posY")).toReal();
        int height = m_query->value(rec.indexOf("height")).toInt();
        int width  = m_query->value(rec.indexOf("width")).toInt();
        int red    = m_query->value(rec.indexOf("colorR")).toInt();
        int green  = m_query->value(rec.indexOf("colorG")).toInt();
        int blue   = m_query->value(rec.indexOf("colorB")).toInt();

        Node *node = static_cast<Node *>(m_scene->getObjectById(id));
        node->setPos(QPointF(posX, posY));
        node->setStandardColor(QColor(red, green, blue));
        node->setSize(QSize(width, height));
        //Workaround for wrong selection after loading
        node->setSelected(true);
        node->setSelected(false);
    }
}

void GraphLoader::loadLinksVisual()
{
    if(!m_query->exec(SQL_SELECT_LINKVISUAL_TABLE))
    {
        qDebug() << "[GraphLoader]:" << m_query->lastError().text();
    }

    QSqlRecord rec = m_query->record();

    while (m_query->next())
    {
        int id     = m_query->value(rec.indexOf("id")).toInt();
        bool hasDestinArrow = m_query->value(rec.indexOf("sourceArrow")).toBool();
        bool hasSourceArrow = m_query->value(rec.indexOf("destinArrow")).toBool();
        int red    = m_query->value(rec.indexOf("colorR")).toInt();
        int green  = m_query->value(rec.indexOf("colorG")).toInt();
        int blue   = m_query->value(rec.indexOf("colorB")).toInt();

        LinkVisual *link = static_cast<LinkVisual *>(m_scene->getObjectById(id));
        link->setDefaultArrows(hasDestinArrow, hasSourceArrow);
        link->setStandardColor(QColor(red, green, blue));
        //Workaround for wrong selection
        link->setSelected(true);
        link->setSelected(false);
    }
}
