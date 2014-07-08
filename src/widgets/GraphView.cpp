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
#include <QTableView>
#include <QMenu>
#include <QMessageBox>

#include "../common/IScaObjectFile.h"
#include "../common/IScaObjectTextBlock.h"
#include "../common/IScaObjectBinaryBlock.h"
#include "../common/IScaObjectDirectory.h"
#include "../common/IScaObjectSymbol.h"
#include "../common/IScaObjectLine.h"
#include "../common/IScaObjectIdentifier.h"
#include "../common/IScaObjectGroup.h"
#include "../common/ScaObjectConverter.h"
#include "../ScaMIMEDataProcessor.h"
#include "../GraphModel.h"
#include "../GraphFilter.h"
#include "../GraphTableProxyModel.h"
#include "../visual/ObjectVisual.h"
#include "../NumericalConstants.h"

GraphView::GraphView(QWidget *parent) :
    QGraphicsView(parent),
    m_temp(NULL),
    m_model(NULL),
    m_changingLinkMode(false),
    m_menu(new QMenu(this))
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

GraphView::GraphView(GraphScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent),
    m_temp(NULL),
    m_model(NULL),
    m_changingLinkMode(false),
    m_menu(new QMenu(this))
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    connect(this->scene(), SIGNAL(selectionChanged()), this, SLOT(updateActions()));
}

void GraphView::dragEnterEvent(QDragEnterEvent *event)
{
    m_temp = NULL;
    const QMimeData *mime = event->mimeData();
    QString path = mime->property("fromPath").toString();
    qDebug() << "[GraphView]: path = " << path;
    //Add object to model and get it's id + create it's visual representation
    m_tempId = m_model->addObject(event->mimeData());
    qDebug() << "[GraphView]: temp_id = " << m_tempId;
    if (m_tempId < 0)
    {
        return;
    }
    QModelIndex index = m_model->index(m_tempId, 0);
    m_model->setData(index, QVariant(true), onSceneRole);

    event->acceptProposedAction();
    scene()->clearSelection();
    m_temp = static_cast<Node *>(scene()->getObjectById(m_tempId));
    if (m_temp == NULL)
    {
        qDebug() << "[GraphView]: Unable to find new element in scene.";
    }
    m_temp->setSelected(true);
    emit goToObject(m_tempId);
}

void GraphView::dragMoveEvent(QDragMoveEvent *event)
{
    m_temp->setPos(mapToScene(event->pos()));
    emit itemMoved(m_tempId);
}

void GraphView::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    if (m_tempId >= 0)
    {
        QModelIndex index = m_model->index(m_tempId, 0);
        QVariant var = m_model->data(index, rawObjectRole);
        IScaObject *obj = NULL;
        obj = qvariant_cast<IScaObject *>(var);
        if (obj == NULL)
        {
            obj = qvariant_cast<Link *>(var);
        }
        if (obj == NULL)
        {
            qDebug() << "[GraphView]: cant cast object while leaving dragEvent";
            return;
        }
        if (obj->getAnnotation().isEmpty())
        {
            qDebug() << "[GraphView]: empty annotation -> delete it from model";
            //We went out of scene, delete created item
            m_model->removeObject(m_tempId);
        }
        else
        {
            qDebug() << "[GraphView]: Annotation not empty -> hide element";
            m_model->setData(index, QVariant(false), onSceneRole);
        }
    }
    scene()->update();
    emit goToObject(m_tempId);
    QGraphicsView::dragLeaveEvent(event);
}

void GraphView::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "[GraphView]: end of dragEvent - dropped";
    //We just save new item
    m_temp = NULL;
    m_tempId = -1;
}

void GraphView::ShowContextMenu(const QPoint &pos)
{
    //Move menu
    QPoint globalPos = viewport()->mapToGlobal(pos);

    m_menu->exec(globalPos);
}

void GraphView::moveTo(const QModelIndex &index)
{
    QTableView *view = qobject_cast<QTableView *>(QObject::sender());
    GraphTableProxyModel *tableProxy = static_cast<GraphTableProxyModel *>(view->model());
    if (tableProxy == NULL)
    {
        qDebug() << "[GraphView]: can't cast sender of signal";
        return;
    }
    QVariant var = tableProxy->data(QModelIndex(), objectIdListRole);
    mapIntToInt idMap = qvariant_cast<mapIntToInt>(var);
    foreach(int id, idMap)
    {
        qDebug() << "[GraphView]: (table, model):(" << id << "," << idMap[id] << ")";
    }

    int modelRow = idMap.value(index.row(), -1);
    ObjectVisual *obj = scene()->getObjectById(modelRow);
    if (obj != NULL)
    {
        qDebug() << "[GraphView]: moving to #" << modelRow <<
                    "(tabled as#" << index.row() << ")=" << obj;
        centerOn(obj);
    }
}

void GraphView::runTool(const QString &tool)
{
    if(!hasFocus())
    {
        return;
    }

    QList<ObjectVisual *> objects = scene()->selectedObjects();
    if(objects.size() != 1)
    {
        return;
    }

    QString filePath;

    int id = scene()->getObjectId(objects.at(0));
    QVariant var = m_model->data(m_model->index(id, 0), rawObjectRole);
    IScaObject *object = qvariant_cast<IScaObject *>(var);
    if((object != NULL) &&
            (object->getType() == IScaObject::FILE ||
            object->getType() == IScaObject::DIRECTORY))
    {
        filePath = object->getFile().filePath();
        emit runCommand(tool, filePath);
    }
}

void GraphView::removeSelectedObjects()
{
    QSet<int> ids = scene()->selectedObjectsIds().toSet();
    qDebug() << "[GraphView]: removing " << ids;
    IScaObject *obj;
    QSet<int> rawIdsToRemove;
    rawIdsToRemove += ids;
    //First get all objects that are inside each other
    foreach (int id, ids)
    {
        obj = m_model->getObjectById(id);
        if (obj == NULL)
        {
            continue;
        }
        //Find first group
        if (obj->getType() == IScaObject::GROUP)
        {
            IScaObjectGroup *group = static_cast<IScaObjectGroup *>(obj);
            QList<IScaObjectGroup *> rollback;
            rollback += group;
            //Recoursively delete groups' objects
            while (!rollback.empty())
            {
                IScaObject *obj = rollback.takeFirst();
                if (obj->getType() == IScaObject::GROUP)
                {
                    IScaObjectGroup *gr = static_cast<IScaObjectGroup *>(obj);
                    foreach(int i, gr->getObjects())
                    {
                        IScaObject *maybeGroup = m_model->getObjectById(i);
                        if (maybeGroup->getType() == IScaObject::GROUP)
                        {
                            rollback.push_back(static_cast<IScaObjectGroup *>(maybeGroup));
                        }
                        //Add these object to delete too
                        rawIdsToRemove += i;
                    }
                }
            }
        }
    }
    //Just delete everything now
    foreach (int id, rawIdsToRemove)
    {
        m_model->removeObject(id);
    }
    emit goToObject(WRONG_OBJECT_INDEX);
}

void GraphView::mouseDoubleClickEvent(QMouseEvent *event)
{
    ObjectVisual *visObject = NULL;
    visObject = static_cast<ObjectVisual *>(itemAt(event->pos()));
    if (visObject == NULL)
    {
        QGraphicsView::mouseDoubleClickEvent(event);
        return;
    }
    if (visObject->getType() == ObjectVisual::LINK)
    {
        //No logics to go with if it is link
        return;
    }
    qDebug() << "[GraphView]: got object to go to";
    int id = scene()->getObjectId(visObject);
    QVariant var = m_model->data(m_model->index(id, 0), rawObjectRole);
    IScaObject *object = qvariant_cast<IScaObject *>(var);
    if (object != NULL)
    {
        emit goToObject(object);
    }
}

void GraphView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_C:
        {
            connectSelectedObjects();
            break;
        }
    case Qt::Key_Delete:
        {
            removeSelectedObjects();
            emit goToObject(WRONG_OBJECT_INDEX);
            break;
        }
    }
}

GraphScene *GraphView::scene() const
{
    return dynamic_cast<GraphScene *>(QGraphicsView::scene());
}

QMenu *GraphView::getMenu() const
{
    return m_menu;
}

void GraphView::setMenu(QMenu *menu)
{
    m_menu->deleteLater();
    m_menu = menu;
}

void GraphView::exportToImage(const QString &path)
{
    QRectF renderZone = scene()->itemsBoundingRect();
    renderZone.adjust(-DEFAULT_IMAGE_ADJUSTING, -DEFAULT_IMAGE_ADJUSTING, DEFAULT_IMAGE_ADJUSTING, DEFAULT_IMAGE_ADJUSTING);
    const int width = renderZone.width();
    const int height = renderZone.height();

    QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(QColor(Qt::white).rgb());
    QPainter painter(&img);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene()->render(&painter, QRectF(0, 0, width, height), renderZone);
    painter.end();
    if (!img.save(path))
    {
        QMessageBox::warning(this, IMAGE_SAVE_ERROR_TITLE, IMAGE_SAVE_ERROR_TEXT.arg(path), QMessageBox::Ok);
    }
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

    if(scene() != NULL)
    {
        disconnect(scene(), SIGNAL(selectionChanged()), this, SLOT(updateActions()));
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

    connect(scene(), SIGNAL(selectionChanged()), this, SLOT(updateActions()));
}

void GraphView::editAnnotation(int id)
{
    // TODO (LeoSko) "Edit annotation" probably shouldn't be in model
    m_model->editAnnotation(id);
    emit goToObject(id);
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *item = NULL;
    item = itemAt(event->pos());
    ObjectVisual *objVisual = NULL;
    //Selection logics goes here
    if (item != NULL)
    {
        objVisual = dynamic_cast<ObjectVisual *>(item);
        if (m_temp != objVisual)
        {
            m_tempId = scene()->getObjectId(objVisual);
            m_temp = objVisual;
        }
        bool ctrlFlag = QApplication::keyboardModifiers().testFlag(Qt::ControlModifier);
        //nothing was selected->select under cursor
        if (scene()->selectedItems().isEmpty())
        {
            item->setSelected(true);
            //If we click with Ctrl, also go to object in other views
            if (ctrlFlag)
            {
                if (objVisual != NULL)
                {
                    IScaObject *object = m_model->getObjectById(m_tempId);
                    if (object != NULL)
                    {
                        emit goToObject(object);
                        emit goToObject(m_tempId);
                    }
                }
                return;
            }
            emit goToObject(m_tempId);
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
                emit goToObject(m_tempId);
            }
            else
            {
                emit goToObject(m_tempId);
                //item under cursor is selected->we are happy about it

            }
        }
    }
    else
    {
        //no item under cursor->clear selection
        scene()->clearSelection();
        emit goToObject(WRONG_OBJECT_INDEX);
    }

    //Process availability to change link's connection
    if (objVisual != NULL)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (objVisual->getType() == ObjectVisual::LINK)
            {
                LinkVisual *link = static_cast<LinkVisual *>(objVisual);
                QPointF from = link->getSource(),
                        to = link->getDestin();
                QPointF eventPos = mapToScene(event->pos());
                //Look at ends of link and check if we clicked close enough to move them
                if ((from - eventPos).manhattanLength() < CHANGE_LINK_CLICK_RADIUS)
                {
                    m_changingLinkMode = true;
                    m_linkSetsNewSource = true;
                }
                if ((to - eventPos).manhattanLength() < CHANGE_LINK_CLICK_RADIUS)
                {
                    m_changingLinkMode = true;
                    m_linkSetsNewSource = false;
                }
            }
        }
    }

    if (event->button() == Qt::RightButton)
    {
        if (objVisual != NULL)
        {
            objVisual->setSelected(true);
            ShowContextMenu(event->pos());
        }
        return;
    }
    QGraphicsView::mousePressEvent(event);
    // TODO (LeoSko) Somehow line above unselects links
    // In future it need some exploration, but it
    // Shouldn't take much preformance for now
    if (item != NULL)
    {
        item->setSelected(true);
    }
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsItem *item = NULL;
    item = itemAt(event->pos());
    ObjectVisual *obj = NULL;
    obj = dynamic_cast<ObjectVisual *>(item);
    if (m_changingLinkMode == true)
    {
        //If we want to set new link to this item
        LinkVisual *linkVis = static_cast<LinkVisual *>(m_temp);
        if (linkVis != NULL)
        {
            if (m_linkSetsNewSource)
            {
                linkVis->setSource(mapToScene(event->pos()));
            }
            else
            {
                linkVis->setDestin(mapToScene(event->pos()));
            }
        }
    }
    if (obj != NULL)
    {
        if (obj->getType() == ObjectVisual::LINK)
        {
            LinkVisual *link = static_cast<LinkVisual *>(obj);
            QPointF from = link->getSource(),
                    to = link->getDestin();
            QPointF eventPos = mapToScene(event->pos());
            if ((from - eventPos).manhattanLength() < CHANGE_LINK_CLICK_RADIUS
                    || (to - eventPos).manhattanLength() < CHANGE_LINK_CLICK_RADIUS)
            {
                setCursor(Qt::PointingHandCursor);
            }
            else
            {
                setCursor(Qt::CrossCursor);
            }
        }
        else
        {
            setCursor(Qt::CrossCursor);
        }
        //qDebug() << "[GraphView]: on " << obj;
        //Check if we are moving item so that we use some button
        if (event->buttons() != Qt::NoButton)
        {
            emit itemMoved(m_tempId);
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_changingLinkMode == true)
    {
        QGraphicsItem *item = NULL;
        item = itemAt(event->pos());
        ObjectVisual *obj = NULL;
        obj = dynamic_cast<ObjectVisual *>(item);
        //Check if we finish dragging on some item, which is not link itself
        if (obj != NULL && obj != m_temp)
        {
            Link *currentLink = static_cast<Link *>(m_model->getObjectById(m_tempId));
            int idAboutToBeLinked = scene()->getObjectId(obj);
            IScaObject *newObj = m_model->getObjectById(idAboutToBeLinked);
            if (m_linkSetsNewSource)
            {
                //Disconnect from old objects
                int oldFromId = currentLink->getObjectFrom();
                IScaObject *oldFrom = m_model->getObjectById(oldFromId);
                ObjectVisual *oldConnectedObj = scene()->getObjectById(oldFromId);
                oldFrom->disconnectLink(m_tempId);
                oldConnectedObj->disconnectLink(m_tempId);
                //Refresh link in link
                currentLink->setObjectFrom(idAboutToBeLinked);
            }
            else
            {
                int oldToId = currentLink->getObjectTo();
                IScaObject *oldTo = m_model->getObjectById(oldToId);
                ObjectVisual *oldConnectedObj = scene()->getObjectById(oldToId);
                oldTo->disconnectLink(m_tempId);
                oldConnectedObj->disconnectLink(m_tempId);
                currentLink->setObjectTo(idAboutToBeLinked);
            }
            scene()->getObjectById(idAboutToBeLinked)->addLink(m_tempId);
            newObj->addLink(m_tempId);
            //To simply emit other views of model that link has changed we 'replace' item with itself
            m_model->replaceObject(currentLink, m_tempId);
            emit goToObject(m_tempId);
        }
        else
        {
            scene()->refreshLinkPos(m_tempId);
        }
        m_changingLinkMode = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}


void GraphView::connectSelectedObjects()
{
    QList<ObjectVisual *> objects = scene()->selectedObjects();

    if(objects.size() != 2)
    {
        return;
    }

    int srcId = scene()->getObjectId(objects.at(0));
    int destId = scene()->getObjectId(objects.at(1));
    m_model->connectObjects(srcId, destId);
}

void GraphView::setSelectedLinkLeftArrow(bool hasArrow)
{
    QList<LinkVisual *> links = scene()->selectedLinks();
    if(links.size() != 1)
    {
        return;
    }

    LinkVisual *link = links.at(0);
    if (hasArrow)
    {
        if (!link->hasLeftArrow())
        {
            links.at(0)->setDefaultArrows(true);
        }
    }
    else
    {
        links.at(0)->removeLeftArrow();
    }
}


void GraphView::setSelectedLinkRightArrow(bool hasArrow)
{
    QList<LinkVisual *> links = scene()->selectedLinks();
    if(links.size() != 1)
    {
        return;
    }

    LinkVisual *link = links.at(0);
    if (hasArrow)
    {
        if (!link->hasRightArrow())
        {
            links.at(0)->setDefaultArrows(false);
        }
    }
    else
    {
        links.at(0)->removeRightArrow();
    }
}

void GraphView::editSelectedAnnotation()
{
    QList<ObjectVisual *> objects = scene()->selectedObjects();
    if(objects.size() != 1)
    {
        return;
    }

    int id = scene()->getObjectId(objects.at(0));
    editAnnotation(id);
    emit goToObject(id);
}

void GraphView::convertSelectedNodeToText()
{
    QList<ObjectVisual *> objects = scene()->selectedObjects();
    m_tempId = scene()->getObjectId(objects.at(0));
    m_model->convert(m_tempId, IScaObject::TEXTBLOCK);
    emit goToObject(m_tempId);
}

void GraphView::convertSelectedNodeToIdentifier()
{
    QList<ObjectVisual *> objects = scene()->selectedObjects();
    m_tempId = scene()->getObjectId(objects.at(0));
    m_model->convert(m_tempId, IScaObject::IDENTIFIER);
    emit goToObject(m_tempId);
}

void GraphView::updateActions()
{
    QList<Node *> nodes = scene()->selectedNodes();
    QList<LinkVisual *> links = scene()->selectedLinks();
    QList<ObjectVisual *> objects = scene()->selectedObjects();

    if (nodes.size() > 0)
    {
        bool hasGroup = false;
        foreach (Node *node, nodes)
        {
            int id = scene()->getObjectId(node);
            IScaObject *obj = m_model->getObjectById(id);
            if (obj == NULL)
            {
                continue;
            }
            if (obj->getType() == IScaObject::GROUP)
            {
                hasGroup = true;
                break;
            }
        }
        emit canUngroup(hasGroup);
    }

    emit objectsSelected(objects.size());
    emit objectsCanConnect(nodes.size() + links.size() == 2);
    emit objectSelected(objects.size() == 1);
    emit nodeSelected(nodes.size() == 1);
    emit linkSelected(links.size() == 1);
    emit canCreateGroup(nodes.size() > 1);

    if (links.size() == 1)
    {
        if(links.at(0)->getSource().x() < links.at(0)->getDestin().x())
        {
            emit linkHasLeftArrow(links.at(0)->getSourceArrow() != NULL);
            emit linkHasRightArrow(links.at(0)->getDestinArrow() != NULL);
        }
        else
        {
            emit linkHasLeftArrow(links.at(0)->getDestinArrow() != NULL);
            emit linkHasRightArrow(links.at(0)->getSourceArrow() != NULL);
        }
    }
    else
    {
        emit linkHasLeftArrow(false);
        emit linkHasRightArrow(false);
    }

    if (nodes.size() == 1)
    {
        Node *node = nodes.at(0);
        int id = scene()->getObjectId(node);
        IScaObject *obj = m_model->getObjectById(id);

        emit canConvertToText(ScaObjectConverter::canConvert(obj, IScaObject::TEXTBLOCK));
        emit canConvertToIdent(ScaObjectConverter::canConvert(obj, IScaObject::IDENTIFIER));
    }
    else
    {
        emit canConvertToText(false);
        emit canConvertToIdent(false);
    }
}

void GraphView::createGroupFromSelection()
{
    QList<int> ids = scene()->selectedObjectsIds();
    QPointF pointToAdd = scene()->centerOfMass(ids);
    QSet<int> groupIds = QSet<int>::fromList(ids);
    foreach (int id, ids)
    {
        IScaObject *obj = m_model->getObjectById(id);
        QList<IScaObject *> rollBack;
        rollBack += obj;
        while (!rollBack.empty())
        {
            // We form list with links to add to group like we do with them in GraphLoader::loadLinks()
            QList<int> links = rollBack.takeFirst()->getLinks();
            foreach (int linkId, links)
            {
                groupIds += linkId;
                rollBack += m_model->getObjectById(linkId);
            }
        }
    }
    // Remove outer group links that were accidentially selected
    foreach (int id, groupIds)
    {
        IScaObject *obj = m_model->getObjectById(id);
        if (obj->getType() == IScaObject::LINK)
        {
            Link *link = static_cast<Link *>(obj);
            if (!groupIds.contains(link->getObjectFrom()) &&
                !groupIds.contains(link->getObjectTo()))
            {
                groupIds.remove(id);
            }
        }
    }

    qDebug() << "[GraphView]: group: " << groupIds;
    // Now in groupIds we have all needed objects to include in group
    IScaObjectGroup *group = ObjectCreator::createGroup(groupIds.toList(), m_model);
    int groupId = m_model->addObject(group, -1, true);
    ObjectVisual *groupVis = scene()->getObjectById(groupId);
    groupVis->setPos(pointToAdd);
    //Save this point to later move it's objects
    IScaObjectGroupVisual *grVis = static_cast<IScaObjectGroupVisual *>(groupVis);
    if (grVis != NULL)
    {
        grVis->savePoint();
        grVis->setSelected(true);
    }

    // Object are hidden, just add needed links to outer objects
    foreach (int id, groupIds)
    {
        IScaObject *obj = m_model->getObjectById(id);
        if (obj->getType() == IScaObject::LINK)
        {
            Link *link = static_cast<Link *>(obj);
            if (groupIds.contains(link->getObjectTo()) &&
                !groupIds.contains(link->getObjectFrom()))
            {
                int linkId = m_model->connectObjects(groupId, link->getObjectFrom());
                m_model->setAnnotation(linkId, link->getAnnotation());
                scene()->refreshLinkPos(linkId);
                LinkVisual *linkVis = static_cast<LinkVisual *>(scene()->getObjectById(linkId));
                LinkVisual *oldLink = static_cast<LinkVisual *>(scene()->getObjectById(id));
                linkVis->setDefaultArrows(oldLink->hasSourceArrow(), oldLink->hasDestinArrow());
            }
            else if (groupIds.contains(link->getObjectFrom()) &&
                     !groupIds.contains(link->getObjectTo()))
            {
                int linkId = m_model->connectObjects(groupId, link->getObjectTo());
                m_model->setAnnotation(linkId, link->getAnnotation());
                scene()->refreshLinkPos(linkId);
                LinkVisual *linkVis = static_cast<LinkVisual *>(scene()->getObjectById(linkId));
                LinkVisual *oldLink = static_cast<LinkVisual *>(scene()->getObjectById(id));
                linkVis->setDefaultArrows(oldLink->hasSourceArrow(), oldLink->hasDestinArrow());
            }
            else
            {
                // Do nothing, it is inner group link
            }
        }
        // Unselect old objects
        scene()->getObjectById(id)->setSelected(false);
    }
    emit goToObject(groupId);
}

void GraphView::ungroupSelectedObjects()
{
    QList<int> ids = scene()->selectedObjectsIds();
    qDebug() << "[GraphView]: ungrouping " << ids;
    QList<int> objectsToSelect;
    IScaObject *obj;
    foreach (int id, ids)
    {
        obj = m_model->getObjectById(id);
        if (obj == NULL)
        {
            continue;
        }
        if (obj->getType() == IScaObject::GROUP)
        {
            IScaObjectGroup *group = static_cast<IScaObjectGroup *>(obj);
            QList<int> objectsFromGroup = group->getObjects();
            scene()->adjustNodesToGroup(objectsFromGroup, id);

            objectsToSelect += objectsFromGroup;
            m_model->removeObject(id);
        }
    }
    qDebug() << "[GraphView]: ungroupSelectedObjects(), toSelect: " << objectsToSelect;
    ObjectVisual *objVis = NULL;
    foreach (int id, objectsToSelect)
    {
        objVis = scene()->getObjectById(id);
        objVis->setSelected(true);
        if (objVis->getType() == ObjectVisual::LINK)
        {
            scene()->refreshLinkPos(id);
        }
    }
    emit goToObject(WRONG_OBJECT_INDEX);
}
