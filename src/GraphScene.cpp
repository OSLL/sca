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
    removeLinks(links);
    removeNodes(nodes);
}

IScaObjectFileVisual *GraphScene::addFileVisual(IScaObjectFile *object)
{
    IScaObjectFileVisual *node = new IScaObjectFileVisual(object);

    addItem(node);
    return node;
}

IScaObjectSymbolVisual *GraphScene::addSymbolVisual(IScaObjectSymbol *object)
{
    IScaObjectSymbolVisual *node = new IScaObjectSymbolVisual(object);

    addItem(node);
    return node;
}

IScaObjectLineVisual *GraphScene::addLineVisual(IScaObjectLine *object)
{
    IScaObjectLineVisual *node = new IScaObjectLineVisual(object);

    addItem(node);
    return node;
}

IScaObjectBinaryBlockVisual *GraphScene::addBinaryBlockVisual(IScaObjectBinaryBlock *object)
{
    IScaObjectBinaryBlockVisual *node = new IScaObjectBinaryBlockVisual(object);

    addItem(node);
    return node;
}

IScaObjectIdentifierVisual *GraphScene::addIdentifierVisual(IScaObjectIdentifier *object)
{
    IScaObjectIdentifierVisual *node = new IScaObjectIdentifierVisual(object);

    addItem(node);
    return node;
}

IScaObjectTextBlockVisual *GraphScene::addTextBlockFromNode(Node *node)
{
    ScaObjectConverter conv;
    switch(node->type())
    {
    case IScaObject::IDENTIFIER:
        {
            qDebug() << "Converting id to text";
            IScaObjectTextBlockVisual *new_obj =
                    conv.getTextBlockFromIdentifier(
                        static_cast<IScaObjectIdentifierVisual *>(node), true);
            addItem(new_obj);
            return new_obj;
        }
    case IScaObject::BINARYBLOCK:
        {
            qDebug() << "Converting binary to text";
            //Waiting for dividing block into 2 classes
            return NULL;
        }
    default:
        break;
    }
    qDebug() << "No conversion";
    return static_cast<IScaObjectTextBlockVisual *>(node);
}

IScaObjectIdentifierVisual *GraphScene::addIdentifierFromNode(Node *node)
{
    ScaObjectConverter conv;
    switch(node->getObject()->getType())
    {
    case IScaObject::TEXTBLOCK:
        {
            qDebug() << "Converting text to id";
            IScaObjectIdentifierVisual *new_obj =
                    conv.getIdentifierFromBlock(
                        static_cast<IScaObjectTextBlockVisual *>(node), true);
            addItem(new_obj);
            return new_obj;
        }
    case IScaObject::BINARYBLOCK:
        {
            qDebug() << "Converting binary to id";
            //Waiting for dividing block into 2 classes
            return NULL;
        }
    default:
        break;
    }
    qDebug() << "No conversion";
    return static_cast<IScaObjectIdentifierVisual *>(node);
}

IScaObjectTextBlockVisual *GraphScene::addBinaryBlockFromNode(Node *node)
{
    ScaObjectConverter conv;
    switch(node->getObject()->getType())
    {
    case IScaObject::IDENTIFIER:
        {
        qDebug() << "Converting id to binary";
            return NULL;
        }
    case IScaObject::TEXTBLOCK:
        {
        qDebug() << "Converting text to binary";
            //Waiting for dividing block into 2 classes
            return NULL;
        }
    default:
        break;
    }
    qDebug() << "No conversion";
    return static_cast<IScaObjectTextBlockVisual *>(node);
}

IScaObjectDirectoryVisual *GraphScene::addDirVisual(IScaObjectDirectory *object)
{
    IScaObjectDirectoryVisual *node = new IScaObjectDirectoryVisual(object);

    addItem(node);
    return node;
}

IScaObjectTextBlockVisual *GraphScene::addTextBlockVisual(IScaObjectTextBlock *object)
{
    IScaObjectTextBlockVisual *node = new IScaObjectTextBlockVisual(object);

    addItem(node);
    return node;
}

Node *GraphScene::addNode(IScaObject *object)
{
    Node *node = new Node(object, DEFAULT_NODE_COLOR);

    addItem(node);
    return node;
}

LinkVisual *GraphScene::addLinkVisual(Node *source, Node *dest, Link *object)
{
    LinkVisual *link = new LinkVisual(source, dest, object);

    addItem(link);
    return link;
}

void GraphScene::removeNodes(QList<Node *> nodes)
{
    qDebug() << "Removing " << nodes.size() << " nodes";
    foreach(Node *node, nodes)
    {
        delete node;
    }
}

void GraphScene::removeLinks(QList<LinkVisual *> links)
{
    qDebug() << "Removing " << links.size() << " links";
    foreach(LinkVisual *link, links)
    {
        delete link;
    }
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
    switch(type)
    {
        case IScaObject::FILE:
        {
            IScaObjectFile *fileObject = static_cast<IScaObjectFile *>(object);
            IScaObjectFileVisual *visObject = addFileVisual(fileObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::DIRECTORY:
        {
            IScaObjectDirectory *dirObject = static_cast<IScaObjectDirectory *>(object);
            IScaObjectDirectoryVisual *visObject = addDirVisual(dirObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::TEXTBLOCK:
        {
            IScaObjectTextBlock *textObject = static_cast<IScaObjectTextBlock *>(object);
            IScaObjectTextBlockVisual*visObject = addTextBlockVisual(textObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::BINARYBLOCK:
        {
            IScaObjectBinaryBlock *binaryObject = static_cast<IScaObjectBinaryBlock *>(object);
            IScaObjectBinaryBlockVisual *visObject = addBinaryBlockVisual(binaryObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::LINE:
        {
            IScaObjectLine *lineObject = static_cast<IScaObjectLine *>(object);
            IScaObjectLineVisual *visObject = addLineVisual(lineObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::IDENTIFIER:
        {
            IScaObjectIdentifier *identObject = static_cast<IScaObjectIdentifier *>(object);
            IScaObjectIdentifierVisual *visObject = addIdentifierVisual(identObject);
            m_objects.insert(id, visObject);
            break;
        }
        case IScaObject::SYMBOL:
        {
            IScaObjectSymbol *symbolObject = static_cast<IScaObjectSymbol *>(object);
            IScaObjectSymbolVisual *visSymbol = addSymbolVisual(symbolObject);
            m_objects.insert(id, visSymbol);
            break;
        }
        case IScaObject::LINK:
        {
            Link *link = static_cast<Link *>(object);
            LinkVisual *visLink = addLinkVisual(NULL, NULL, link);
            m_objects.insert(id, visLink);
            break;
        }
    }
}

GraphModel *GraphScene::getModel() const
{
    return m_model;
}

void GraphScene::setModel(GraphModel *model)
{
    m_model = model;
}

void GraphScene::updateObjects(QModelIndex row, QModelIndex column)
{
    qDebug() << "Update object";

    quint64 id = row.row();
    ObjectVisual *visObject = getObjectById(id);

    //Construction for working with QVarint(pointer)
    IScaObject *object = qvariant_cast<IScaObject *>(m_model->data(row));

    if(visObject == NULL)
    {
        addObjectVisual(object, id);
    }
}

