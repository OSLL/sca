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
 * \file GraphView.cpp
 * \brief GraphView implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphView.h"
#include <QDragEnterEvent>
#include <QInputDialog>
#include <QApplication>
#include <QDebug>
#include <QUrl>
#include "widgets/GraphViewContextMenu.h"
#include "common/IScaObjectFile.h"
#include "common/IScaObjectTextBlock.h"
#include "common/IScaObjectBinaryBlock.h"
#include "common/IScaObjectDirectory.h"
#include "common/IScaObjectSymbol.h"
#include "common/IScaObjectLine.h"
#include "common/IScaObjectIdentifier.h"
#include "common/ScaObjectConverter.h"
#include "ScaMIMEDataProcessor.h"
#include "GraphModel.h"
#include "GraphFilter.h"
#include "../NumericalConstants.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent),
    m_temp(NULL),
    m_model(NULL)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_menu = new GraphViewContextMenu(this);
}

GraphView::GraphView(GraphScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent),
    m_temp(NULL),
    m_model(NULL)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_menu = new GraphViewContextMenu(this);
}

void GraphView::dragEnterEvent(QDragEnterEvent *event)
{
    m_temp = NULL;
    //Add object to model and get it's id + create it's visual representation
    m_tempId = m_model->addObject(event->mimeData());
    if (m_tempId < 0)
    {
        return;
    }

    event->acceptProposedAction();
    scene()->clearSelection();
    m_temp = static_cast<Node *>(scene()->getObjectById(m_tempId));
    if (m_temp == NULL)
    {
        qDebug() << "Unable to find new element in scene.";
    }
    m_temp->setSelected(true);
}

void GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    m_temp->setPos(mapToScene(event->pos()));
}

void GraphView::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    if (m_tempId >= 0)
    {
        //We went out of scene, delete created item
        m_model->removeObject(m_tempId);
    }
}

void GraphView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
    //We just save new item
    m_temp = NULL;
}

void GraphView::ShowContextMenu(const QPoint &pos)
{
    //Move menu
    QPoint globalPos = viewport()->mapToGlobal(pos);

    //Get what is selected
    QList<Node *> nodes = scene()->selectedNodes();
    QList<LinkVisual *> links = scene()->selectedLinks();
    QList<QGraphicsItem *> items = scene()->selectedItems();

    ScaObjectConverter conv;

    //Get actions to interact with
    QAction *del = m_menu->getActionByName(DELETE_ITEMS);
    QAction *toText = m_menu->getActionByName(TO_TEXT_BLOCK);
    QAction *toIdentifier = m_menu->getActionByName(TO_IDENTIFIER);
    QAction *conAct = m_menu->getActionByName(CONNECT_NODES);
    QAction *setLeftArrow = m_menu->getActionByName(LEFT_ARROW);
    QAction *setRightArrow = m_menu->getActionByName(RIGHT_ARROW);
    QAction *editAnnotation = m_menu->getActionByName(EDIT_ANNOTATION);

    //#Setting up menu#//
    //Reset to defaults
    m_menu->resetToDefault();
    //Setting connection available only if 2 nodes or links selected
    conAct->setEnabled(nodes.size() == 2 || links.size() == 2);
    //Editing annotation only if there is only one link under selection
    editAnnotation->setEnabled(links.size() == 1);

    if (!links.isEmpty() || !nodes.isEmpty())
    {
        m_tempId = scene()->getObjectId(m_temp);
    }
    if (links.size() == 1)
    {
        setLeftArrow->setEnabled(true);
        setRightArrow->setEnabled(true);
        bool hasLeftArrow = false;
        bool hasRightArrow = false;

        if(links.at(0)->getSource().x() < links.at(0)->getDestin().x())
        {
            hasLeftArrow = links.at(0)->getSourceArrow() != NULL;
            hasRightArrow = links.at(0)->getDestinArrow() != NULL;
        }
        else
        {
            hasRightArrow = links.at(0)->getSourceArrow() != NULL;
            hasLeftArrow = links.at(0)->getDestinArrow() != NULL;
        }
        setLeftArrow->setChecked(hasLeftArrow);
        setRightArrow->setChecked(hasRightArrow);
    }
    else
    {
        setLeftArrow->setEnabled(false);
        setRightArrow->setEnabled(false);
    }


    //Allow deleting only if something selected
    del->setEnabled(!items.isEmpty());

    //Converting available for proper types
    if (nodes.size() == 1)
    {
        Node *node = nodes.at(0);
        int id = scene()->getObjectId(node);
        QVariant var = m_model->data(m_model->index(id, 0), rawObjectRole);
        IScaObject *obj = qvariant_cast<IScaObject *>(var);
        toText->setEnabled(conv.canConvert(obj, IScaObject::TEXTBLOCK));
        toIdentifier->setEnabled(conv.canConvert(obj, IScaObject::IDENTIFIER));
    }

    //Show menu
    QAction *action = NULL;
    action = m_menu->exec(globalPos);
    if (action == NULL)
    {
        return;
    }

    //Process chosen action
    if (action == conAct)
    {
        ObjectVisual *src, *dest;
        if (nodes.size() == 2)
        {
            src = nodes.at(0);
            dest = nodes.at(1);
        }
        else
        {
            src = links.at(0),
            dest = links.at(1);
        }
        int srcId = scene()->getObjectId(src);
        int destId = scene()->getObjectId(dest);
        m_model->connectObjects(srcId, destId);
        return;
    }
    else if (action == toText)
    {
        m_model->convert(m_tempId, IScaObject::TEXTBLOCK);
        return;
    }
    else if (action == toIdentifier)
    {
        m_model->convert(m_tempId, IScaObject::IDENTIFIER);
        return;
    }
    else if (action == del)
    {
        foreach(LinkVisual *link, links)
        {
            m_model->removeObject(scene()->getObjectId(link));
        }
        foreach(Node *node, nodes)
        {
            m_model->removeObject(scene()->getObjectId(node));
        }

    }
    else if (action == setLeftArrow)
    {
        if (setLeftArrow->isChecked())
            links.at(0)->setDefaultArrows(true);
        else
            links.at(0)->removeSourceArrow();
    }
    else if (action == setRightArrow)
    {
        if (setRightArrow->isChecked())
            links.at(0)->setDefaultArrows(false);
        else
            links.at(0)->removeDestinArrow();
    }
    else if (action == editAnnotation)
    {
        int id = scene()->getObjectId(links.at(0));
        editLinkAnnotation(id);
    }
}

void GraphView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_C:
        {
            QList<Node *> items = scene()->selectedNodes();
            if(items.size() == 2)
            {
                Node *src = items.at(0);
                Node *dest = items.at(1);
                quint32 srcId = scene()->getObjectId(src);
                quint32 destId = scene()->getObjectId(dest);
                m_model->connectObjects(srcId, destId);
            }
        }
        break;
    case Qt::Key_Delete:
        {
            foreach(LinkVisual *link, scene()->selectedLinks())
            {
                m_model->removeObject(scene()->getObjectId(link));
            }
            foreach(Node *node, scene()->selectedNodes())
            {
                m_model->removeObject(scene()->getObjectId(node));
            }

        }
        break;
    }
}

GraphScene *GraphView::scene() const
{
    return dynamic_cast<GraphScene *>(QGraphicsView::scene());
}

GraphViewContextMenu *GraphView::getMenu() const
{
    return m_menu;
}

void GraphView::setMenu(GraphViewContextMenu *menu)
{
    m_menu->deleteLater();
    m_menu = menu;
}

void GraphView::exportToImage(const QString path)
{

    QRectF renderZone = scene()->itemsBoundingRect();
    renderZone.adjust(-10, -10, 10, 10);
    const int width = renderZone.width();
    const int height = renderZone.height();

    QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter painter(&img);
    scene()->render(&painter, QRectF(0, 0, width, height),renderZone);
    painter.end();
    img.save(path);
}
GraphModel *GraphView::getModel() const
{
    return m_model;
}

void GraphView::setModel(GraphModel *model)
{
    GraphScene *sc = scene();
    if (m_model != NULL && sc != NULL)
    {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
                   sc, SLOT(updateObjects(QModelIndex, QModelIndex)));
        disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                   sc, SLOT(removeObject(QModelIndex, int, int)));
    }

    m_model = model;
    if(sc != NULL)
    {
        connect(m_model, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
                sc, SLOT(updateObjects(QModelIndex, QModelIndex)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                sc, SLOT(removeObject(QModelIndex, int, int)));
    }
    sc->setModel(m_model);
}

void GraphView::setScene(GraphScene *graphScene)
{
    if (m_model != NULL && scene() != NULL)
    {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                   scene(), SLOT(updateObjects(QModelIndex, QModelIndex)));
        disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                   scene(), SLOT(removeObject(QModelIndex,int,int)));
    }

    QGraphicsView::setScene(graphScene);
    if(m_model != NULL)
    {
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                graphScene, SLOT(updateObjects(QModelIndex, QModelIndex)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                scene(), SLOT(removeObject(QModelIndex,int,int)));
    }
    graphScene->setModel(m_model);
}

void GraphView::editLinkAnnotation(int id)
{
    m_model->editLinkAnnotation(id);
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *item = NULL;
    item = itemAt(event->pos());
    //Selection logics goes here
    if (item != NULL)
    {
        bool ctrlFlag = QApplication::keyboardModifiers().testFlag(Qt::ControlModifier);
        //nothing was selected->select under cursor
        if (scene()->selectedItems().isEmpty())
        {
            item->setSelected(true);
            if (ctrlFlag)
            {
                return;
            }
        }
        else
        {
            //item under cursor is not selected->clear selection, select it
            if (scene()->selectedItems().indexOf(item) == -1)
            {
                if (!ctrlFlag)
                {
                    scene()->clearSelection();
                }
                item->setSelected(true);
                if (ctrlFlag)
                {
                    return;
                }
            }
            else
            {
                //item under cursor is selected->we are happy about it
            }
        }
    }
    else
    {
        //no item under cursor->clear selection
        scene()->clearSelection();
    }

    if (event->button() == Qt::RightButton)
    {
        Node *node = NULL;
        node = dynamic_cast<Node *>(item);
        if (node != NULL)
        {
            m_temp = node;
        }
        //        ShowContextMenu(event->pos());
        return;
    }
    QGraphicsView::mousePressEvent(event);
    // TODO (LeoSko) Somehow line above unselects links
    //In future it need some exploration, but it
    //Shouldn't take much preformance for now
    if (event->button() == Qt::LeftButton)
    {
        if (item != NULL)
        {
            item->setSelected(true);
        }
    }
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
