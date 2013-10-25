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
#include "common/IScaObjectFile.h"
#include "common/IScaObjectBlock.h"
#include "common/IScaObjectDirectory.h"
#include "common/IScaObjectSymbol.h"
#include "common/IScaObjectLine.h"
#include "common/IScaObjectIdentifier.h"
#include "ScaMIMEDataProcessor.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent), temp(NULL)
{
}

GraphView::GraphView(GraphScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent),temp(NULL)
{
}

void GraphView::dragEnterEvent(QDragEnterEvent *event)
{
    //Turn off interaction for drag-n-drop processing, otherwise it will fail
    setInteractive(false);
    //Create temporary node to see where it will be placed
    //Here you can also process different types of drops
    if (temp != NULL)
        temp = NULL;
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        ScaMIMEDataProcessor processor(event->mimeData());
        IScaObject *object = processor.makeObject();
        switch (object->getType())
        {
        case IScaObject::FILE:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_FILE_VISUAL_WIDTH / 2,
                                   DEFAULT_FILE_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addFileVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectFile *>(object));
                return;
            }
        case IScaObject::DIRECTORY:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_DIR_VISUAL_WIDTH / 2,
                                   DEFAULT_DIR_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addDirVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectDirectory *>(object));
                return;
            }
        case IScaObject::BINARYBLOCK:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_BINARY_BLOCK_VISUAL_WIDTH / 2,
                                   DEFAULT_BINARY_BLOCK_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addBinaryBlockVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectBlock *>(object));
                return;
            }
        case IScaObject::TEXTBLOCK:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_TEXT_BLOCK_VISUAL_WIDTH / 2,
                                   DEFAULT_TEXT_BLOCK_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addTextBlockVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectBlock *>(object));
                return;
            }
        case IScaObject::IDENTIFIER:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_IDENTIFIER_VISUAL_WIDTH / 2,
                                   DEFAULT_IDENTIFIER_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addIdentifierVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectIdentifier *>(object));
                return;
            }
        case IScaObject::SYMBOL:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_SYMBOL_VISUAL_WIDTH / 2,
                                   DEFAULT_SYMBOL_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addSymbolVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectSymbol *>(object));
                return;
            }
        case IScaObject::LINE:
            {
                QPoint evPos = pos(),
                       centerDelta(DEFAULT_LINE_VISUAL_WIDTH / 2,
                                   DEFAULT_LINE_VISUAL_HEIGHT / 2);
                temp = GraphView::scene()->addLineVisual(
                            mapToScene(evPos) - evPos - centerDelta,
                            static_cast<IScaObjectLine *>(object));
                return;
            }
        }
    }
}

void GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    if (temp != NULL)
        temp->setPos(event->pos());
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
        if (temp != NULL)
            GraphView::scene()->removeItem(temp);
        return;
    }
}

void GraphView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event)
    dragLeaveEvent(0, true);
}

void GraphView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_C)
    {
        QList<Node *> items = scene()->selectedNodes();
        if(items.size() == 2)
        {
            scene()->addLinkVisual(items.at(1), items.at(0));
        }
    }
}

GraphScene *GraphView::scene() const
{
    return dynamic_cast<GraphScene *>(QGraphicsView::scene());
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
