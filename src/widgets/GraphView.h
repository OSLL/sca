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

#include "../GraphScene.h"
class GraphFilter;
class GraphModel;

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphView(QWidget *parent = 0);
    explicit GraphView(GraphScene *scene, QWidget *parent = 0);
    GraphScene *scene() const;

    QMenu *getMenu() const;
    void setMenu(QMenu *menu);

    void exportToImage(const QString path);

    void editAnnotation(int id);
    GraphModel *getModel() const;
    void setModel(GraphModel *model);
    void setScene(GraphScene *graphScene);

private:
    //This is used for drag-n-drop technology
    ObjectVisual *m_temp;
    int m_tempId;
    GraphModel *m_model;
    bool m_changingLinkMode;
    bool m_linkSetsNewSource;
    QMenu *m_menu;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event = 0, bool = false);
    void dropEvent(QDropEvent * event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void goToObject(IScaObject *);
    void goToObject(int id);
    void itemMoved(int id);
    void linkSelected(bool);
    void nodeSelected(bool);
    void objectsCanConnect(bool);
    void objectSelected(bool);
    void objectsSelected(bool);
    void canConvertToText(bool);
    void canConvertToIdent(bool);
    void canCreateGroup(bool);
    void canUngroup(bool);
    void linkHasLeftArrow(bool);
    void linkHasRightArrow(bool);

    void runCommand(QString, QString);

public slots:
    void ShowContextMenu(const QPoint &pos);
    void moveTo(const QModelIndex &index);
    void runTool(const QString &tool);
    void removeSelectedObjects();
    void connectSelectedObjects();
    void setSelectedLinkLeftArrow(bool hasArrow);
    void setSelectedLinkRightArrow(bool hasArrow);
    void editSelectedAnnotation();
    void convertSelectedNodeToText();
    void convertSelectedNodeToIdentifier();
    void updateActions();
    void createGroupFromSelection();
    void ungroupSelectedObjects();

}; // class GraphView

#endif //_GraphView_H_04F3BA35_873F_445D_88DC_4D314948D9C9_INCLUDED_
