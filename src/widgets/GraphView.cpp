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
    //Turn off interaction for drag-n-drop processing, otherwise it will fail
    setInteractive(false);
    //Create temporary node to see where it will be placed
    //Here you can also process different types of drops
    m_temp = NULL;

    const QMimeData *mimeData = event->mimeData();

    //Add object to model and get it's id + create it's visual representation
    int id = m_model->addObject(mimeData);
    QPoint evPos = event->pos();
    QPointF pos = mapToScene(evPos) - evPos;

    //Get object by id
    m_temp = dynamic_cast<Node*>(scene()->getObjectById(id));
    if(m_temp != NULL)
    {
        //So we created object
        event->acceptProposedAction();
        m_temp->setPos(pos);
        scene()->clearSelection();
        m_temp->setSelected(true);
    }
}

void GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    if (m_temp != NULL)
    {
        m_temp->setPos(mapToScene(event->pos()));
    }
}

void GraphView::dragLeaveEvent(QDragLeaveEvent *event)
{
    GraphView::dragLeaveEvent(event, false);
}

void GraphView::dragLeaveEvent(QDragLeaveEvent *event, bool dropped)
{
    Q_UNUSED(event)
    setInteractive(true);
    if (!dropped)
    {
        if (m_temp != NULL)
            GraphView::scene()->removeItem(m_temp);
        return;
    }
    if (m_temp->getObject()->getType() == IScaObject::TEXTBLOCK)
    {
        QPoint pos = mapFromScene(m_temp->pos());
        ShowContextMenu(pos);
    }
}

void GraphView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event)
    dragLeaveEvent(0, true);
}


void GraphView::ShowContextMenu(const QPoint &pos)
{
    //Move menu
    QPoint globalPos = viewport()->mapToGlobal(pos);


    QList<Node *> nodes = scene()->selectedNodes();
    QList<LinkVisual *> links = scene()->selectedLinks();
    QList<QGraphicsItem *> items = scene()->selectedItems();

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
    //Setting connection available only if 2 nodes selected
    conAct->setEnabled(nodes.size() == 2);
    //Editing annotation only if there is only one link under selection
    editAnnotation->setEnabled(links.size() == 1);

    if (!links.isEmpty() || !nodes.isEmpty())
    {
        m_tempId = m_model->getId(m_temp->getObject());
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

    //Reset conversions
    toText->setEnabled(false);
    toIdentifier->setEnabled(false);
    //Converting available for proper types
    if (nodes.size() == 1)
    {
        Node *node = nodes.at(0);
        ScaObjectConverter conv(m_model);
        toText->setEnabled(conv.canConvert(node, IScaObject::TEXTBLOCK));
        toIdentifier->setEnabled(conv.canConvert(node, IScaObject::IDENTIFIER));
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
        Node *src = nodes.at(0);
        Node *dest = nodes.at(1);
        m_model->connectObjects(src->getObject(), dest->getObject());
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
        // TODO (LeoSko) removing should be in GraphModel, not GraphScene
        scene()->removeLinks(scene()->selectedLinks());
        scene()->removeNodes(scene()->selectedNodes());
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
        editLinkAnnotation(links.at(0));
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
            m_model->connectObjects(src->getObject(), dest->getObject());
        }
    }
        break;
    case Qt::Key_Delete:
    {
        scene()->removeLinks(scene()->selectedLinks());
        scene()->removeNodes(scene()->selectedNodes());
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
GraphModel *GraphView::model() const
{
    return m_model;
}

void GraphView::setModel(GraphModel *model)
{
    if (m_model != NULL && scene() != NULL)
    {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                   scene(), SLOT(updateObjects(QModelIndex, QModelIndex)));
    }

    m_model = model;
    if(scene() != NULL)
    {
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                scene(), SLOT(updateObjects(QModelIndex, QModelIndex)));
    }
    scene()->setModel(m_model);
}

void GraphView::setScene(GraphScene *graphScene)
{
    if (m_model != NULL && scene() != NULL)
    {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                   scene(), SLOT(updateObjects(QModelIndex, QModelIndex)));
    }

    QGraphicsView::setScene(graphScene);
    if(m_model != NULL)
    {
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                graphScene, SLOT(updateObjects(QModelIndex, QModelIndex)));
    }
    graphScene->setModel(m_model);
}

void GraphView::editLinkAnnotation(LinkVisual *link)
{
    if (link == NULL)
        return;
    bool ok = false;
    QString new_annotation =
            QInputDialog::getText(this, EDIT_ANNOTATION,
                                  EDIT_ANNOTATION_LABEL, QLineEdit::Normal,
                                  link->getAnnotationText(),
                                  &ok);
    if (ok == true && !new_annotation.isEmpty())
    {
        link->setAnnotation(new_annotation);
    }
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
