/*
 * Copyright 2013  Nikita Razdobreev  exzo0mex@gmail.com
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
 * \file GraphScene.cpp
 * \brief GraphScene implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphScene.h"
#include "common/ScaObjectConverter.h"
#include "StringConstants.h"
#include "GraphModel.h"
#include <QDebug>
#include <QInputDialog>
#include <QVariant>

GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height,
                       QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
}

GraphScene::~GraphScene()
{
    QList<QGraphicsItem *> items;
    QList<Node *> nodes;
    QList<LinkVisual *> links;
    items = this->items();
    foreach(QGraphicsItem *item, items)
    {
        LinkVisual *link = NULL;
        Node *node = NULL;
        node = dynamic_cast<Node *>(item);
        if (node != NULL)
        {
            nodes.push_back(node);
            continue;
        }
        link = dynamic_cast<LinkVisual *>(item);
        if (link != NULL)
        {
            links.push_back(link);
        }
    }
}

IScaObjectFileVisual *GraphScene::addFileVisual(IScaObjectFile *object)
{
    QFileInfo fileInfo = object->getFile();
    IScaObjectFileVisual *node = new IScaObjectFileVisual(fileInfo);

    addItem(node);
    return node;
}

IScaObjectSymbolVisual *GraphScene::addSymbolVisual(IScaObjectSymbol *object)
{
    char symbol = object->getSymbol();
    IScaObjectSymbolVisual *node = new IScaObjectSymbolVisual(symbol);

    addItem(node);
    return node;
}

IScaObjectLineVisual *GraphScene::addLineVisual(IScaObjectLine *object)
{
    QString line = object->getLine();
    IScaObjectLineVisual *node = new IScaObjectLineVisual(line);

    addItem(node);
    return node;
}

IScaObjectBinaryBlockVisual *GraphScene::addBinaryBlockVisual(IScaObjectBinaryBlock *object)
{
    QByteArray data = object->getData();
    IScaObjectBinaryBlockVisual *node = new IScaObjectBinaryBlockVisual(data);

    addItem(node);
    return node;
}

IScaObjectIdentifierVisual *GraphScene::addIdentifierVisual(IScaObjectIdentifier *object)
{
    QString identifier = object->getIdentifier();
    IScaObjectIdentifierVisual *node = new IScaObjectIdentifierVisual(identifier);

    addItem(node);
    return node;
}

IScaObjectDirectoryVisual *GraphScene::addDirVisual(IScaObjectDirectory *object)
{
    QFileInfo fileInfo = object->getFile();
    IScaObjectDirectoryVisual *node = new IScaObjectDirectoryVisual(fileInfo);

    addItem(node);
    return node;
}

IScaObjectTextBlockVisual *GraphScene::addTextBlockVisual(IScaObjectTextBlock *object)
{
    QString text = object->getText();
    IScaObjectTextBlockVisual *node = new IScaObjectTextBlockVisual(text);

    addItem(node);
    return node;
}

Node *GraphScene::addNode(IScaObject *object)
{
    Node *node = new Node(DEFAULT_NODE_COLOR);

    addItem(node);
    return node;
}

LinkVisual *GraphScene::addLinkVisual(QString annotation)
{
    LinkVisual *link = new LinkVisual(annotation);

    addItem(link);
    return link;
}

void GraphScene::removeObject(ObjectVisual *object)
{
    quint64 id = getObjectId(object);
    qDebug() << "Removing object #" << id;
    m_objects.remove(id);
    removeItem(object);
    delete(object);
}


QList<Node *> GraphScene::selectedNodes()
{
    QList<Node *> nodes;
    foreach(QGraphicsItem *item, selectedItems())
    {
        Node *node = NULL;
        node = dynamic_cast<Node *>(item);
        if (node != NULL)
        {
            nodes.push_back(node);
        }
    }
    return nodes;
}

QList<LinkVisual *> GraphScene::selectedLinks()
{
    QList<LinkVisual *> links;
    foreach(QGraphicsItem *item, selectedItems())
    {
        LinkVisual *link = NULL;
        link = dynamic_cast<LinkVisual *>(item);
        if (link != NULL)
        {
            links.push_back(link);
        }
    }
    return links;
}

void GraphScene::refreshLinkPosTo(quint64 linkId, QPointF pos)
{
    if (!m_objects.contains(linkId))
    {
        return;
    }
    LinkVisual *link = static_cast<LinkVisual *>(m_objects.value(linkId, NULL));
    link->refreshGeometryTo(pos);
}

void GraphScene::refreshLinkPosFrom(quint64 linkId, QPointF pos)
{

    if (!m_objects.contains(linkId))
    {
        return;
    }
    LinkVisual *link = static_cast<LinkVisual *>(m_objects.value(linkId, NULL));
    link->refreshGeometryFrom(pos);
}


ObjectVisual *GraphScene::getObjectById(quint64 id)
{
    if(!m_objects.contains(id))
    {
        return NULL;
    }

    return m_objects[id];
}

ObjectVisual *GraphScene::addObjectVisual(IScaObject *object, int id)
{
    IScaObject::IScaObjectType type = object->getType();
    qDebug() << "Adding #" << id << ", type: " << type;
    switch(type)
    {
    case IScaObject::FILE:
    {
        IScaObjectFile *fileObject = static_cast<IScaObjectFile *>(object);
        IScaObjectFileVisual *visObject = addFileVisual(fileObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::DIRECTORY:
    {
        IScaObjectDirectory *dirObject = static_cast<IScaObjectDirectory *>(object);
        IScaObjectDirectoryVisual *visObject = addDirVisual(dirObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::TEXTBLOCK:
    {
        IScaObjectTextBlock *textObject = static_cast<IScaObjectTextBlock *>(object);
        IScaObjectTextBlockVisual *visObject = addTextBlockVisual(textObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::BINARYBLOCK:
    {
        IScaObjectBinaryBlock *binaryObject = static_cast<IScaObjectBinaryBlock *>(object);
        IScaObjectBinaryBlockVisual *visObject = addBinaryBlockVisual(binaryObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::LINE:
    {
        IScaObjectLine *lineObject = static_cast<IScaObjectLine *>(object);
        IScaObjectLineVisual *visObject = addLineVisual(lineObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::IDENTIFIER:
    {
        IScaObjectIdentifier *identObject = static_cast<IScaObjectIdentifier *>(object);
        IScaObjectIdentifierVisual *visObject = addIdentifierVisual(identObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::SYMBOL:
    {
        IScaObjectSymbol *symbolObject = static_cast<IScaObjectSymbol *>(object);
        IScaObjectSymbolVisual *visObject = addSymbolVisual(symbolObject);
        visObject->setPos(m_posToAdd);
        m_objects.insert(id, visObject);
        break;
    }
    case IScaObject::LINK:
    {
        Link *link = static_cast<Link *>(object);
        quint64 sourceId = m_model->getId(link->getObjectFrom());
        quint64 destinId = m_model->getId(link->getObjectTo());
        QString annotation = link->getAnnotation();
        Node *sourceNode = static_cast<Node *>(m_objects[sourceId]);
        Node *destinNode = static_cast<Node *>(m_objects[destinId]);
        LinkVisual *visLink = addLinkVisual(annotation);
        m_objects.insert(id, visLink);
        sourceNode->addLinkFrom(id);
        destinNode->addLinkTo(id);

        Q_ASSERT(visLink != NULL && sourceNode != NULL && destinNode != NULL);

        break;
    }
    }
}

quint64 GraphScene::getObjectId(ObjectVisual *object)
{
    return m_objects.key(object);
}

GraphModel *GraphScene::getModel() const
{
    return m_model;
}

void GraphScene::setModel(GraphModel *model)
{
    m_model = model;
}

void GraphScene::updateObjectVisual(IScaObject *object, int id)
{
    qDebug() << "Updating object #" << id << "Type " << object->getType();

    if (object == NULL || !m_objects.contains(id))
        return;

    ObjectVisual *objectVis = m_objects.take(id);

    if(objectVis->getType() == ObjectVisual::NODE)
    {
        Node *prevObject = static_cast<Node *>(objectVis);
        QPointF pos = prevObject->pos();

        addObjectVisual(object, id);
        Node *node = static_cast<Node *>(m_objects[id]);
        node->setPos(pos);
        node->setLinksFrom(prevObject->getLinksFrom());
        node->setLinksTo(prevObject->getLinksTo());
    }

    removeItem(objectVis);
    delete(objectVis);
}

void GraphScene::removeObject(const QModelIndex &parent, int first, int last)
{
    if(!(first == last))
    {
        return;
    }
    //TODO (zo0mer): we must delete ids of removed link from nodes
    ObjectVisual *object = getObjectById(first);
    removeObject(object);
}

void GraphScene::updateObjects(QModelIndex leftTop, QModelIndex rightBottom)
{
    qDebug() << "Update object #" << leftTop.row();

    quint64 id = leftTop.row();//Get object that changed
    QVariant var = m_model->data(leftTop, Qt::DecorationRole);
    IScaObject *object = NULL;
    object = qvariant_cast<IScaObject *>(var);
    //Maybe it is on scene?
    ObjectVisual *visObject = getObjectById(id);

    if (object == NULL) //Object no longer exists, but it was there
    {
        removeItem(visObject);
        delete visObject;
        return;
    }

    if (visObject == NULL)
    {
        addObjectVisual(object, id);
    }
    else
    {
        updateObjectVisual(object, id);
    }

}

