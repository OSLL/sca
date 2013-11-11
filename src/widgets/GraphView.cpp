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

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent),
    m_temp(NULL)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_menu = new GraphViewContextMenu(this);
}

GraphView::GraphView(GraphScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent),
    m_temp(NULL)
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

    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        ScaMIMEDataProcessor processor(event->mimeData());
        IScaObject *object = processor.makeObject();
        QPoint evPos = event->pos();
        switch (object->getType())
        {
        case IScaObject::FILE:
        {
            m_temp = GraphView::scene()->addFileVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectFile *>(object));
            break;
        }
        case IScaObject::DIRECTORY:
        {
            m_temp = GraphView::scene()->addDirVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectDirectory *>(object));
            break;
        }
        case IScaObject::BINARYBLOCK:
        {
            m_temp = GraphView::scene()->addBinaryBlockVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectBinaryBlock *>(object));
            break;
        }
        case IScaObject::TEXTBLOCK:
        {
            m_temp = GraphView::scene()->addTextBlockVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectTextBlock *>(object));
            break;
        }
        case IScaObject::IDENTIFIER:
        {
            m_temp = GraphView::scene()->addIdentifierVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectIdentifier *>(object));
            break;
        }
        case IScaObject::SYMBOL:
        {
            m_temp = GraphView::scene()->addSymbolVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectSymbol *>(object));
            break;
        }
        case IScaObject::LINE:
        {
            m_temp = GraphView::scene()->addLineVisual(
                        mapToScene(evPos) - evPos,
                        static_cast<IScaObjectLine *>(object));
            break;
        }
        }
        if (m_temp != NULL)
        {
            scene()->clearSelection();
            m_temp->setSelected(true);
        }
    }
}

void GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    if (m_temp != NULL)
        m_temp->setPos(mapToScene(event->pos()));
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
    QAction *setSrcArrow = m_menu->getActionByName(SET_LINK_SOURCE_ARROW);
    QAction *setDestArrow = m_menu->getActionByName(SET_LINK_DESTINATION_ARROW);


    //#Setting up menu#//
    //Setting connection available only if 2 nodes selected
    conAct->setEnabled(nodes.size() == 2);

    if(links.size() == 1)
    {
        setSrcArrow->setEnabled(true);
        setDestArrow->setEnabled(true);
        bool hasSrcArrow = links.at(0)->getSourceArrow() != NULL;
        bool hasDesArrow = links.at(0)->getDestinArrow() != NULL;
        setSrcArrow->setChecked(hasSrcArrow);
        setDestArrow->setChecked(hasDesArrow);
    }
    else
    {
        setSrcArrow->setEnabled(false);
        setDestArrow->setEnabled(false);
    }


    //Allow deleting only if something selected
    del->setEnabled(!items.isEmpty());

    //Reset conversions
    toText->setEnabled(false);
    toIdentifier->setEnabled(false);
    //Converting available for proper types
    if (nodes.size() == 1)
    {
        qDebug() << "One node!";
        Node *node = nodes.at(0);
        ScaObjectConverter *conv = new ScaObjectConverter();
        toText->setEnabled(conv->canConvert(node, IScaObject::TEXTBLOCK));
        toIdentifier->setEnabled(conv->canConvert(node, IScaObject::IDENTIFIER));
        delete conv;
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
        scene()->addLinkVisual(nodes.at(1), nodes.at(0));
        return;
    }
    else if (action == toText)
    {
        m_temp = scene()->addTextBlockFromNode(m_temp);
        return;
    }
    else if (action == toIdentifier)
    {
        m_temp = scene()->addIdentifierFromNode(m_temp);
        return;
    }
    else if (action == del)
    {
        scene()->removeLinks(scene()->selectedLinks());
        scene()->removeNodes(scene()->selectedNodes());
    }
    else if(action == setSrcArrow)
    {
        if(setSrcArrow->isChecked())
            links.at(0)->setDefaultArrows(true, false);
        else
            links.at(0)->removeSourceArrow();
    }
    else if(action == setDestArrow)
    {
        if(setDestArrow->isChecked())
            links.at(0)->setDefaultArrows(false, true);
        else
            links.at(0)->removeDestinArrow();
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
            scene()->addLinkVisual(items.at(1), items.at(0));
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

GraphViewContextMenu *GraphView::menu() const
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

void GraphView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QGraphicsItem *item = NULL;
        item = itemAt(event->pos());
        if (item != NULL)
        {
            //nothing was selected->select under cursor
            if (scene()->selectedItems().isEmpty())
            {
                item->setSelected(true);
            }
            else
            {
                //item under cursor is not selected->clear selection, select it
                if (scene()->selectedItems().indexOf(item) == -1)
                {
                    scene()->clearSelection();
                    item->setSelected(true);
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

        Node *node = NULL;
        node = dynamic_cast<Node *>(item);
        if (node != NULL)
        {
            m_temp = node;
        }
        ShowContextMenu(event->pos());
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
