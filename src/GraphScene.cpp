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
#include "NumericalConstants.h"
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
    Q_UNUSED(object);
    Node *node = new Node(DEFAULT_NODE_COLOR);

    addItem(node);
    return node;
}

LinkVisual *GraphScene::addLinkVisual(Link *object)
{
    LinkVisual *link = new LinkVisual(object);

    addItem(link);
    return link;
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

void GraphScene::refreshLinkPos(int linkId)
{
    if (!m_objects.contains(linkId))
    {
        return;
    }
    LinkVisual *link = static_cast<LinkVisual *>(m_objects.value(linkId, NULL));
    Q_ASSERT(link);
    QVariant var = m_model->data(m_model->index(linkId, 0), rawObjectRole);
    Link *objLink = qvariant_cast<Link *>(var);

    int fromId = objLink->getObjectFrom(),
            toId = objLink->getObjectTo();
    // TODO (LeoSko) It really seems we don't have nice interface there, right?
    Node    *from = static_cast<Node *>(m_objects.value(fromId, NULL)),
            *to = static_cast<Node *>(m_objects.value(toId, NULL));
    link->refreshGeometry(from->pos(), to->pos());
}

void GraphScene::refreshAll()
{
    qDebug() << "Refresh all visual objects";
    QList<QModelIndex> indeces;
    foreach(int id, m_objects.keys())
    {
        //qDebug() << "index #" << id;
        indeces.append(m_model->index(id, 0));
    }

    foreach (QModelIndex index, indeces)
    {
       updateObjects(index, index);
    }
}

ObjectVisual *GraphScene::getObjectById(int id)
{
    return m_objects.value(id, NULL);
}

ObjectVisual *GraphScene::addObjectVisual(IScaObject *object, int id)
{
    if (m_objects.contains(id))
    {
        qDebug() << "Scene already contains object #" << id;
        return NULL;
    }
    IScaObject::IScaObjectType type = object->getType();
    ObjectVisual *visObject = NULL;
    //qDebug() << "Adding #" << id << "-" << type << " to scene.";

    switch(type)
    {
    case IScaObject::FILE:
        {
            IScaObjectFile *fileObject = static_cast<IScaObjectFile *>(object);
            visObject = addFileVisual(fileObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::DIRECTORY:
        {
            IScaObjectDirectory *dirObject = static_cast<IScaObjectDirectory *>(object);
            visObject = addDirVisual(dirObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::TEXTBLOCK:
        {
            IScaObjectTextBlock *textObject = static_cast<IScaObjectTextBlock *>(object);
            visObject = addTextBlockVisual(textObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::BINARYBLOCK:
        {
            IScaObjectBinaryBlock *binaryObject = static_cast<IScaObjectBinaryBlock *>(object);
            visObject = addBinaryBlockVisual(binaryObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::LINE:
        {
            IScaObjectLine *lineObject = static_cast<IScaObjectLine *>(object);
            visObject = addLineVisual(lineObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::IDENTIFIER:
        {
            IScaObjectIdentifier *identObject = static_cast<IScaObjectIdentifier *>(object);
            visObject = addIdentifierVisual(identObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::SYMBOL:
        {
            IScaObjectSymbol *symbolObject = static_cast<IScaObjectSymbol *>(object);
            visObject = addSymbolVisual(symbolObject);
            visObject->setPos(m_posToAdd);
            m_objects.insert(id, visObject);
            break;
        }
    case IScaObject::LINK:
        {
            Link *link = static_cast<Link *>(object);
            Q_ASSERT(link != NULL);
            int sourceId = link->getObjectFrom();
            int destinId = link->getObjectTo();
            Node *sourceNode = static_cast<Node *>(m_objects.value(sourceId, NULL));
            Node *destinNode = static_cast<Node *>(m_objects.value(destinId, NULL));
            visObject = addLinkVisual(link);
            qDebug() << sourceNode << destinNode << visObject;
            Q_ASSERT(visObject != NULL && sourceNode != NULL && destinNode != NULL);
            m_objects.insert(id, visObject);
            sourceNode->addLink(id);
            destinNode->addLink(id);
            break;
        }
    default:
        {
            qDebug() << "Unknown type of object trying to add on scene.";
            break;
        }
    }
    //qDebug() << "Successfully added object to scene.";
    return visObject;
}

int GraphScene::getObjectId(ObjectVisual *object)
{
    return m_objects.key(object);
}

QAbstractItemModel *GraphScene::getModel() const
{
    return m_model;
}

void GraphScene::setModel(QAbstractItemModel *model)
{
    m_model = model;
    refreshAll();
}

void GraphScene::updateObjectVisual(IScaObject *object, int id)
{
    //qDebug() << "Updating existing #" << id << " in scene.";

    if (object == NULL || !m_objects.contains(id))
    {
        return;
    }

    if (object->getType() == IScaObject::LINK)
    {
        LinkVisual *link = static_cast<LinkVisual *>(m_objects[id]);
        link->setAnnotation(object->getAnnotation());
        return;
    }
    //Take it from scene
    ObjectVisual *objectVis = m_objects.take(id);

    //We re-create object, saving some old parameters of it
    QPointF pos = objectVis->pos();
    QList<int> links = objectVis->getLinks();

    //Get new object
    QVariant var = m_model->data(m_model->index(id, 0), rawObjectRole);
    IScaObject *obj = qvariant_cast<IScaObject *>(var);
    Q_ASSERT(obj != NULL);

    //Adds object with old id so we save associations for links
    ObjectVisual *newObject = addObjectVisual(obj, id);
    newObject->setPos(pos);
    newObject->setLinks(links);

    //Remove old one
    removeItem(objectVis);
    delete objectVis;

    //Update for object filtering
    QVariant filtered = m_model->data(m_model->index(id, 0), highlightRole);
    newObject->setFiltered(filtered.toBool());
}

void GraphScene::removeObject(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    //qDebug() << "Removing objects from scene.";
    for (int i = first; i <= last; i++)
    {
        ObjectVisual *obj = m_objects.take(i);
        int linksCount = obj->getLinks().size();
        Q_ASSERT(linksCount == 0);
        //qDebug() << "Removing #" << i << "from scene. Items left: " << m_objects.size();
        if (obj->getType() == ObjectVisual::LINK)
        {
            QVariant var = m_model->data(m_model->index(i, 0), rawObjectRole);
            Link *l = qvariant_cast<Link *>(var);
            Q_ASSERT(l != NULL);
            int fromId = l->getObjectFrom(),
                    toId = l->getObjectTo();
            Node *from = static_cast<Node *>(m_objects[fromId]);
            Node *to = static_cast<Node *>(m_objects[toId]);
            Q_ASSERT(from != NULL && to != NULL);
            from->disconnectLink(i);
            to->disconnectLink(i);
        }
        removeItem(obj);
        delete obj;
    }
}

void GraphScene::updateObjects(QModelIndex leftTop, QModelIndex rightBottom)
{
    Q_UNUSED(rightBottom);
    qDebug() << "Update #" << leftTop.row() << " to scene.";

    //Get object that changed
    int id = leftTop.row();
    QVariant var = m_model->data(leftTop, rawObjectRole);
    IScaObject *object = NULL;
    object = qvariant_cast<IScaObject *>(var);

    if (object == NULL)
    {
        object = qvariant_cast<Link *>(var);
    }

    if (object == NULL)
    {
        if (m_objects.contains(id))
        {
            //Object no longer exists, but it was there, so delete it
            removeObject(leftTop, id, id);
        }
        return;
    }

    //Maybe it is already on scene?
    ObjectVisual *visObject = getObjectById(id);

    if (visObject == NULL)
    {
        //It is not on scene, but it is in model
        addObjectVisual(object, id);
        return;
    }
    else
    {
        //It is on scene and in model, update representation
        updateObjectVisual(object, id);
        return;
    }
}
