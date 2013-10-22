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
    if (event->mimeData()->hasUrls())
    {
        QString filePath = event->mimeData()->urls().at(0).path();
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists()) //For different systems it needs to remove first symbol '/'
        {                       //e.g. Windows: /D:/Dir1/Dir2/, but in UNIX: /home/dir1
            filePath.remove(0, 1);
            fileInfo.setFile(filePath);
        }
        if (event->mimeData()->hasText())   //IScaObjectBlock/Line/Symbol/Identifier
        {
            event->acceptProposedAction();
            QPoint evPos = pos(),
                   centerDelta(DEFAULT_BLOCK_VISUAL_WIDTH / 2,
                               DEFAULT_BLOCK_VISUAL_HEIGHT / 2);

            int offset = event->mimeData()->property("position").toInt(),
                length = event->mimeData()->property("length").toInt();
            IScaObjectFile *objFile = new IScaObjectFile(fileInfo);
            IScaObjectBlock *objBlock = new IScaObjectBlock(objFile, offset, length);
            temp = GraphView::scene()->addBlockVisual(mapToScene(evPos) - evPos - centerDelta, objBlock);
            return;
        }
        if (fileInfo.isFile())  //IScaObjectFile
        {
            event->acceptProposedAction();
            qDebug() << fileInfo.filePath();
            QPoint evPos = pos(),
                   centerDelta(DEFAULT_FILE_VISUAL_WIDTH / 2,
                               DEFAULT_FILE_VISUAL_HEIGHT / 2);
            IScaObjectFile *objFile = new IScaObjectFile(fileInfo);
            temp = GraphView::scene()->addFileVisual(mapToScene(evPos) - evPos - centerDelta, objFile);
            return;
        }
        if (fileInfo.isDir())   //IScaObjectDirectory
        {
            event->acceptProposedAction();
            qDebug() << fileInfo.filePath();
            QPoint evPos = pos(),
                   centerDelta(DEFAULT_DIR_VISUAL_WIDTH / 2,
                               DEFAULT_DIR_VISUAL_HEIGHT / 2);
            IScaObjectDirectory *objDir = new IScaObjectDirectory(fileInfo);
            temp = GraphView::scene()->addDirVisual(mapToScene(evPos) - evPos - centerDelta, objDir);
            return;
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

    dragLeaveEvent(0, true);
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
