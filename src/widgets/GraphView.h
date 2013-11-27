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
 * \file GraphView.h
 * \brief Header of GraphView
 * \todo fix ContextMenu for model
 * \todo fox editLinkAnnotation
 * \todo fix node move
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */


#ifndef _GraphView_H_04F3BA35_873F_445D_88DC_4D314948D9C9_INCLUDED_
#define _GraphView_H_04F3BA35_873F_445D_88DC_4D314948D9C9_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */
#include <QGraphicsView>
#include "widgets/GraphViewContextMenu.h"
#include "GraphScene.h"
class GraphFilter;
class GraphModel;

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphView(QWidget *parent = 0);
    explicit GraphView(GraphScene *scene, QWidget *parent = 0);
    GraphScene *scene() const;

    GraphViewContextMenu *getMenu() const;
    void setMenu(GraphViewContextMenu *menu);

    void exportToImage(const QString path);

    void editLinkAnnotation(quint32 id);
    GraphModel *getModel() const;
    void setModel(GraphModel *model);
    void setScene(GraphScene *graphScene);
    void setFilter(GraphFilter *filter);
    void setFilter(QString pattern);
    void removeFilter();
private:
    //This is used for drag-n-drop technology
    Node *m_temp;
    quint32 m_tempId;
    GraphViewContextMenu *m_menu;
    GraphModel *m_model;

public slots:
    void ShowContextMenu(const QPoint &pos);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event = 0, bool = false);
    void dropEvent(QDropEvent * event);
    void keyPressEvent(QKeyEvent *event);
}; // class GraphView


#endif //_GraphView_H_04F3BA35_873F_445D_88DC_4D314948D9C9_INCLUDED_

