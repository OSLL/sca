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

GraphScene::GraphScene(qreal x, qreal y, qreal width, qreal height, QObject * parent) :
    QGraphicsScene(x, y, width, height, parent)
{
}

IScaObjectFileVisual *GraphScene::addFileVisual(const QPointF &coords, IScaObjectFile *object)
{
    IScaObjectFileVisual *node = new IScaObjectFileVisual(coords, object);

    addItem(node);
    return node;
}

IScaObjectSymbolVisual *GraphScene::addSymbolVisual(const QPointF &coords, IScaObjectSymbol *object)
{
    IScaObjectSymbolVisual *node = new IScaObjectSymbolVisual(coords, object);

    addItem(node);
    return node;
}

IScaObjectLineVisual *GraphScene::addLineVisual(const QPointF &coords, IScaObjectLine *object)
{
    IScaObjectLineVisual *node = new IScaObjectLineVisual(coords, object);

    addItem(node);
    return node;
}

IScaObjectBlockVisual *GraphScene::addBinaryBlockVisual(const QPointF &coords, IScaObjectBlock *object)
{

}

IScaObjectIdentifierVisual *GraphScene::addIdentifierVisual(const QPointF &coords, IScaObjectIdentifier *object)
{
    IScaObjectIdentifierVisual *node = new IScaObjectIdentifierVisual(coords, object);

    addItem(node);
    return node;
}

IScaObjectDirectoryVisual *GraphScene::addDirVisual(const QPointF &coords, IScaObjectDirectory *object)
{
    IScaObjectDirectoryVisual *node = new IScaObjectDirectoryVisual(coords, object);

    addItem(node);
    return node;
}

IScaObjectBlockVisual *GraphScene::addTextBlockVisual(const QPointF &coords, IScaObjectBlock *object)
{
    IScaObjectBlockVisual *node = new IScaObjectBlockVisual(coords, object);

    addItem(node);
    return node;
}

Node *GraphScene::addNode(const QPointF &coords, IScaObject *object)
{
    Node *node = new Node(coords, object);

    addItem(node);
    return node;
}

LinkVisual *GraphScene::addLinkVisual(Node *source, Node *dest)
{
    LinkVisual *link = new LinkVisual(source, dest);

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

QGraphicsItem *GraphScene::addNode(const float x, const float y, IScaObject *object)
{
    return addNode(QPointF(x, y), object);
}
