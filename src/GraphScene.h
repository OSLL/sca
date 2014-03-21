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
#include "visual/IScaObjectFileVisual.h"
#include "visual/IScaObjectDirectoryVisual.h"
#include "visual/IScaObjectTextBlockVisual.h"
#include "visual/IScaObjectBinaryBlockVisual.h"
#include "visual/IScaObjectSymbolVisual.h"
#include "visual/IScaObjectLineVisual.h"
#include "visual/IScaObjectIdentifierVisual.h"
#include "visual/IScaObjectGroupVisual.h"
#include "visual/Node.h"
#include "visual/LinkVisual.h"
#include "visual/ObjectVisual.h"

class GraphModel;

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    ~GraphScene();

    LinkVisual *addLinkVisual(Link *object);
    ObjectVisual *addObjectVisual(IScaObject *object, int id);

    QList<Node *> selectedNodes();
    QList<LinkVisual *> selectedLinks();
    QList<ObjectVisual *> selectedObjects();

    void clearSelection();

    ObjectVisual *getObjectById(int id) const;
    int getObjectId(ObjectVisual *object);

    QAbstractItemModel *getModel() const;
    void setModel(QAbstractItemModel *model);

    void refreshLinkPos(int linkId);
    void connectLink(IScaObject *object, int id);

    QPoint centerOfMass(const QList<int> &ids);

    QList<int> getIds() const;
private:
    QHash<int, ObjectVisual *> m_objects;

    QAbstractItemModel *m_model;
signals:

public slots:
    void refreshAll();
    void updateObjects(QModelIndex topLeft, QModelIndex rightBottom);
    void updateObjectVisual(IScaObject *object, int id);
    void removeObject(const QModelIndex & parent, int first, int last);
    void clear();

}; // class GraphScene


#endif //_GraphScene_H_52BB4E97_89C3_46B0_A022_D1B1D7E53A87_INCLUDED_
