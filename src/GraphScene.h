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
 * \file GraphScene.h
 * \brief Header of GraphScene
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphScene_H_52BB4E97_89C3_46B0_A022_D1B1D7E53A87_INCLUDED_
#define _GraphScene_H_52BB4E97_89C3_46B0_A022_D1B1D7E53A87_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
#include <QGraphicsScene>
#include <QModelIndex>
#include "common/IScaObject.h"
#include "visual/IScaObjectFileVisual.h"
#include "visual/IScaObjectDirectoryVisual.h"
#include "visual/IScaObjectTextBlockVisual.h"
#include "visual/IScaObjectBinaryBlockVisual.h"
#include "visual/IScaObjectSymbolVisual.h"
#include "visual/IScaObjectLineVisual.h"
#include "visual/IScaObjectIdentifierVisual.h"
#include "visual/Node.h"
#include "visual/LinkVisual.h"
class GraphModel;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    ~GraphScene();

    IScaObjectFileVisual *addFileVisual(IScaObjectFile *object);
    IScaObjectDirectoryVisual *addDirVisual(IScaObjectDirectory *object);
    IScaObjectTextBlockVisual *addTextBlockVisual(IScaObjectTextBlock *object);
    IScaObjectSymbolVisual *addSymbolVisual(IScaObjectSymbol *object);
    IScaObjectLineVisual *addLineVisual(IScaObjectLine *object);
    IScaObjectBinaryBlockVisual *addBinaryBlockVisual(IScaObjectBinaryBlock *object);
    IScaObjectIdentifierVisual *addIdentifierVisual(IScaObjectIdentifier *object);

    quint64 addTextBlockFromNode(Node *node);
    quint64 addIdentifierFromNode(Node *node);
    quint64 addBinaryBlockFromNode(Node *node);

    Node *addNode(IScaObject *object);
    LinkVisual *addLinkVisual(Node *source, Node *dest, Link *object);

    void removeNodes(QList<Node *> nodes);
    void removeLinks(QList<LinkVisual *> links);
    QList<Node *> selectedNodes();
    QList<LinkVisual *> selectedLinks();

    ObjectVisual *getObjectById(quint64 id);

    ObjectVisual *addObjectVisual(IScaObject *object, int id);

    GraphModel *getModel() const;
    void setModel(GraphModel *model);

private:
    QHash<quint64, ObjectVisual *> m_objects;

    QPointF m_posToAdd;
    GraphModel *m_model;
signals:

public slots:
    void updateObjects(QModelIndex topLeft, QModelIndex rightBottom);
}; // class GraphScene


#endif //_GraphScene_H_52BB4E97_89C3_46B0_A022_D1B1D7E53A87_INCLUDED_
