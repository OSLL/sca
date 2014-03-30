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
 * \file GraphSaver.cpp
 * \brief GraphSaver implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphSaver.h"
#include "StringConstants.h"

#include "common/IScaObjectTextBlock.h"
#include "common/IScaObjectIdentifier.h"
#include "common/IScaObjectBinaryBlock.h"
#include "common/IScaObjectSymbol.h"
#include "common/IScaObjectLine.h"
#include "visual/ObjectVisual.h"
#include "visual/Node.h"
#include "StringConstants.h"

#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QObject>

GraphSaver::GraphSaver(const QString &path)
{
    open(path);
}

GraphSaver::~GraphSaver()
{
    m_query->finish();
    m_query->clear();
    m_db.removeDatabase("QSQLITE");
    m_db.close();
    delete m_query;
}

void GraphSaver::insertNode(IScaObject *object, int id, bool isShown)
{
    m_query->prepare(SQL_INSERT_TYPE_PATTERN);
    m_query->bindValue(":id", id);
    m_query->bindValue(":type", object->getType());

    if(!m_query->exec())
    {
        qDebug() << "[GraphSaver]: " <<  m_query->lastError().text();
    }

    m_query->prepare(SQL_INSERT_NODE_PATTERN);
    m_query->bindValue(":id", id);
    m_query->bindValue(":path", object->getFile().filePath());
    m_query->bindValue(":text", object->getContent());
    m_query->bindValue(":annotation", object->getAnnotation());
    m_query->bindValue(":shown", isShown);

    int type = object->getType();
    switch(type)
    {
    case IScaObject::TEXTBLOCK:
    {
        IScaObjectTextBlock *textBlock = static_cast<IScaObjectTextBlock *>(object);
        m_query->bindValue(":offset", textBlock->getOffset());
        m_query->bindValue(":endoffset", textBlock->getEndOffset());
        m_query->bindValue(":length", textBlock->getLength());
    }
        break;

    case IScaObject::IDENTIFIER:
    {
        IScaObjectIdentifier *ident = static_cast<IScaObjectIdentifier *>(object);
        m_query->bindValue(":endoffset", ident->getEndOffset());
        m_query->bindValue(":offset", ident->getOffset());
    }
        break;

    case IScaObject::LINE:
    {
        IScaObjectLine *line = static_cast<IScaObjectLine *>(object);
        m_query->bindValue(":line", line->getLineNumber());
        m_query->bindValue(":offset", line->getOffset());
        m_query->bindValue(":endoffset", line->getEndOffset());
    }
        break;

    case IScaObject::SYMBOL:
    {
        IScaObjectSymbol *symbol = static_cast<IScaObjectSymbol *>(object);
        m_query->bindValue(":offset", symbol->getOffset());
    }
        break;

    case IScaObject::BINARYBLOCK:
    {
        IScaObjectBinaryBlock *binary = static_cast<IScaObjectBinaryBlock *>(object);
        m_query->bindValue(":offset", binary->getOffset());
        m_query->bindValue(":length", binary->getLength());
        m_query->bindValue(":data", binary->getData());
    }
        break;
    }


    if(!m_query->exec())
    {
        qDebug() << "[GraphSaver]: " <<  m_query->lastError().text();
    }
}

bool GraphSaver::open(const QString &path)
{
    if(QFileInfo(path).exists())
    {
        QFile(path).remove();
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "[GraphSaver]: " << m_db.lastError().text();
        return false;
    }

    m_query = new QSqlQuery(m_db);

    return true;
}

bool GraphSaver::createTables()
{
    if(!m_query->exec(SQL_CREATE_NODE_TABLE)
            || !m_query->exec(SQL_CREATE_LINK_TABLE)
            || !m_query->exec(SQL_CREATE_NODEVISUAL_TABLE)
            || !m_query->exec(SQL_CREATE_LINKVISUAL_TABLE)
            || !m_query->exec(SQL_CREATE_TYPE_TABLE))
    {
        qDebug() << "[GraphSaver]: " << m_query->lastError().databaseText();
        return false;
    }

    return true;
}

void GraphSaver::insertLink(Link *link, int id)
{
    m_query->prepare(SQL_INSERT_LINK_PATTERN);
    m_query->bindValue(":id", id);
    qDebug() << "[GraphSaver]: Save connection:" << link->getObjectFrom() << "->" << link->getObjectTo();
    m_query->bindValue(":source", link->getObjectFrom());
    m_query->bindValue(":destin", link->getObjectTo());
    m_query->bindValue(":annotation", link->getAnnotation());
    if(!m_query->exec())
    {
        qDebug() << "[GraphSaver]: " <<  m_query->lastError().text();
    }
}

bool GraphSaver::save(const GraphModel *model, const GraphScene *scene)
{

    if(!m_db.isOpen())
        return false;

    createTables();
    saveModel(model);
    saveScene(scene);

    return true;
}


void GraphSaver::saveModel(const GraphModel *model)
{
    QVariant var = model->data(model->index(0, 0), objectIdListRole);
    QList<int> ids = qvariant_cast<QList<int> >(var);
    QModelIndex index;
    IScaObject *object;

    foreach(int id, ids)
    {
        object = NULL;
        index = model->index(id, 0);
        var = model->data(model->index(id, 0), rawObjectRole);
        object = qvariant_cast<IScaObject *>(var);

        if(object == NULL)
        {
            Link *link = qvariant_cast<Link *>(var);
            insertLink(link, id);
        }
        else
        {
            //Check if object is shown and save that state
            var = model->data(index, onSceneRole);
            insertNode(object, id, var.toBool());
        }
    }
}

void GraphSaver::saveScene(const GraphScene *scene)
{
    QList<int> ids = scene->getIds();
    foreach (int id, ids)
    {
        ObjectVisual *object = scene->getObjectById(id);
        if(object->getType() == ObjectVisual::NODE)
        {
            Node *node = static_cast<Node *>(object);
            insertNodeVisual(node, id);
        }
        else if(object->getType() == ObjectVisual::LINK)
        {
            LinkVisual *link = static_cast<LinkVisual *>(object);
            insertLinkVisual(link, id);
        }
    }

}


void GraphSaver::insertNodeVisual(Node *node, int id)
{
    m_query->prepare(SQL_INSERT_NODEVISUAL_PATTERN);

    QPointF pos = node->pos();
    m_query->bindValue(":posX", pos.x());
    m_query->bindValue(":posY", pos.y());
    m_query->bindValue(":id", id);
    m_query->bindValue(":colorR", node->getStandardColor().red());
    m_query->bindValue(":colorG", node->getStandardColor().green());
    m_query->bindValue(":colorB", node->getStandardColor().blue());
    m_query->bindValue(":width", node->getRect().width());
    m_query->bindValue(":height", node->getRect().height());

    if(!m_query->exec())
    {
        qDebug() << "[GraphSaver]: " <<  m_query->lastError().text();
    }
}

void GraphSaver::insertLinkVisual(LinkVisual *link, int id)
{
    m_query->prepare(SQL_INSERT_LINKVISUAL_PATTERN);

    bool hasSourceArrow = (link->getSourceArrow() != NULL);
    bool hasDestinArrow = (link->getDestinArrow() != NULL);

    m_query->bindValue(":id", id);
    m_query->bindValue(":sourceArrow", hasSourceArrow);
    m_query->bindValue(":destinArrow", hasDestinArrow);
    m_query->bindValue(":colorR", link->getStandardColor().red());
    m_query->bindValue(":colorG", link->getStandardColor().green());
    m_query->bindValue(":colorB", link->getStandardColor().blue());

    if(!m_query->exec())
    {
        qDebug() << "[GraphSaver]: " <<  m_query->lastError().text();
    }
}
