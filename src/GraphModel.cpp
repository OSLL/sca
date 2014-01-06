/*
 * Copyright 2013    exzo0mex@gmail.com
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
 * \file GraphModel.cpp
 * \brief GraphModel implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include "GraphModel.h"
#include "ScaMIMEDataProcessor.h"
#include "common/Link.h"
#include <QDebug>
#include <QInputDialog>
#include <QUrl>
#include "common/ScaObjectConverter.h"
#include "StringConstants.h"

//ID = -1 for objects, which doesn't exist in model
int GraphModel::s_nextID = 0;

GraphModel::GraphModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

GraphModel::~GraphModel()
{
    clear();
}

int GraphModel::connectObjects(int source, int dest, int id, QString annotation)
{
    //qDebug() << "Connecting " << source << " to " << dest;
    int objectId = 0;
    if(id < 0 || m_objects.contains(id))
    {
        objectId = s_nextID;
    }
    else
    {
        objectId = id;
    }

    qDebug() << "[GraphModel]: Connecting " << source << " to " << dest;
    Link *link = new Link(source, dest);
    QModelIndex linkIndex = index(objectId, 0);
    m_objects[source]->addLink(objectId);
    m_objects[dest]->addLink(objectId);

    link->setAnnotation(annotation);
    if (!setData(linkIndex, QVariant::fromValue(link), rawObjectRole))
    {
        qDebug() << "[GraphModel]: Couldn\'t set data.";
    }
    setData(linkIndex, QVariant(true), isShownRole);

    s_nextID = (id > s_nextID) ? id + 1 : s_nextID + 1;
    return objectId;
}

int GraphModel::getObjectIdByPath(const QString &path)
{
    QList<int> ids = m_objects.keys();
    for(int i = 0; i < ids.size(); i++)
    {
        if (m_objects[i]->getFile().absoluteFilePath() == path)
        {
            return ids[i];
        }
    }
    return -1;
}

QString GraphModel::getAnnotationByPath(const QString &path)
{
    foreach(IScaObject *object, m_objects)
    {
        if (object->getFile().absoluteFilePath() == path)
        {
            return object->getAnnotation();
        }
    }
    return QString("");
}

IScaObject *GraphModel::getObjectByPath(const QString &path)
{
    foreach(IScaObject *object, m_objects)
    {
        if (object->getFile().absoluteFilePath() == path)
        {
            return object;
        }
    }
    return NULL;
}

IScaObject *GraphModel::getObjectById(const int &id)
{
    return m_objects.value(id, NULL);
}

int GraphModel::addObject(const QMimeData *mimeData)
{
    QString path = mimeData->property("fromPath").toString();
    qDebug() << "[GraphModel]: path = " << path;
    bool hasPath = (mimeData->hasUrls() || !path.isEmpty());
    if (!hasPath)
    {
        return -1;
    }

    ScaMIMEDataProcessor processor(mimeData);
    IScaObject *objectFromData = processor.makeObject();

    //If we add object out of MIMEData, then show it
    //(-1) - we add object with generic id
    return addObject(objectFromData, -1, true);
}

int GraphModel::addObject(IScaObject *object, int id, bool isShown)
{
    QModelIndex changedIndex;
    if(id < 0)
    {
        changedIndex = index(s_nextID, 0);
        setData(changedIndex, QVariant(isShown), isShownRole);
        setData(changedIndex, QVariant::fromValue(object), rawObjectRole);
        return s_nextID++;
    }
    else
    {
        changedIndex = index(id, 0);
        setData(changedIndex, QVariant(isShown), isShownRole);
        setData(changedIndex, QVariant::fromValue(object), rawObjectRole);
        s_nextID  = (id > s_nextID) ? (id + 1): s_nextID;
        return id;
    }
}

int GraphModel::replaceObject(IScaObject *object, int id)
{
    IScaObject *old = m_objects.value(id, NULL);
    if (old == NULL)
    {
        qDebug() << "[GraphModel]: Object didn't exist before replacing!";
    }

    QModelIndex changedIndex = index(id, 0);
    setData(changedIndex, QVariant::fromValue(object), rawObjectRole);

    return id;
}

int GraphModel::getId(IScaObject *object)
{
    int id = m_objects.key(object);
    //qDebug() << "Requsted id" << id << "in model";
    return id;
}

QModelIndex GraphModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column, m_objects.value(row, NULL));
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    int id = index.row();
    //qDebug() << "[GraphModel]: Data for #" << id;
    if (role == objectIdListRole)
    {
        QList<int> list = m_objects.keys();
        qDebug() << "[GraphModel]: listSize: " << list.size();
        return QVariant::fromValue(list);
    }
    if (id < 0)
    {
        qDebug() << "[GraphModel]: wrong row";
        return QVariant();
    }
    if (!m_objects.contains(id))
    {
        qDebug() << "[GraphModel]: Don\'t have object #" << id;
        return QVariant();
    }
    switch (role)
    {
    case Qt::DisplayRole:   //For standart text views
        {
            return QVariant(m_objects[id]->getInfo());
        }
    case isShownRole:
        {
            return QVariant(m_isShown.value(id, false));
        }
    case rawObjectRole:    //For graphics representation return full object
        {
            IScaObject *object = m_objects[id];
            if (object->getType() == IScaObject::LINK)
            {
                Link *link = static_cast<Link *>(object);
                return QVariant::fromValue(link);
            }
            return QVariant::fromValue(object);
        }
    case highlightRole:
        {
            return QVariant(false);
        }
    default:
        {
            return QVariant();
        }
    }
}

Qt::ItemFlags GraphModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool GraphModel::removeRow(int id, const QModelIndex &parent)
{
    IScaObject *object = m_objects.value(id, NULL);

    if (object == NULL)
    {
        qDebug() << "[GraphModel]: Object doesn\'t exist";
        return false;
    }

    //Remove connections in model of that object first (recursively)
    qDebug() << "[GraphModel]: Removing " << object->getLinks().size() << " links of #" << id << "first.";
    foreach(int link, object->getLinks())
    {
        removeObject(link);
    }

    if (object->getType() == IScaObject::LINK)
    {
        //Disconnect it from source and destination
        freeLink(id);
    }

    //Start removing object itself
    beginRemoveRows(parent, id, id);

    //Remove from container
    m_objects.remove(id);
    m_isShown.remove(id);
    //Remove it from memory
    delete object;

    endRemoveRows();
    qDebug() << "[GraphModel]: Removed #" << id << ". Items left: " << m_objects.size();

    return true;
}

bool GraphModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    for (int i = 0; i < count; i++)
    {
        if (!removeRow(row + i))
        {
            return false;
        }
    }
    return true;
}

int GraphModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << "[GraphModel]: Objects: " << m_objects.size();
    return m_objects.size();
}

bool GraphModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isNull())
    {
        return false;
    }
    if (index.row() < 0)
    {
        return false;
    }

    int id = index.row();
    switch (role)
    {
    case rawObjectRole:
        {
            IScaObject *object = NULL;

            //Try casting to object or link, then add it
            object = qvariant_cast<IScaObject *>(value);
            if (object == NULL)
            {
                object = qvariant_cast<Link *>(value);

            }
            if (object == NULL)
            {
                qDebug() << "[GraphModel]: Can\'t cast object while adding!";
                return false;
            }
            //Successfully casted
            //Set new data (or replace it)
            m_objects.insert(id, object);
            qDebug() << "[GraphModel]: Data set #" << id
                     << ", type: " << object->getTypeName()
                     << ", items total: " << m_objects.size();
            emit dataChanged(index, index);
            return true;
        }
    case isShownRole:
        {
            m_isShown[id] = value.toBool();
            qDebug() << "[GraphModel]: " << (value.toBool()?"Showing":"Hiding")
                     << " #" << id;
            emit dataChanged(index, index);
            return true;
        }
    default:
        {
            return false;
            break;
        }
    }
}

//Returns true if item existed
bool GraphModel::removeObject(int id)
{
    return removeRow(id);
}

bool GraphModel::removeObject(IScaObject *obj)
{
    int id = m_objects.key(obj);
    return removeObject(id);
}

bool GraphModel::freeLink(int link)
{
    if (m_objects[link]->getType() != IScaObject::LINK)
    {
        return false;
    }

    Link *l = static_cast<Link *>(m_objects[link]);
    int source = l->getObjectFrom();
    int destin = l->getObjectTo();

    qDebug() << "[GraphModel]: Freeing link #" << link << "("
             << source << ";" << destin << ")";
    if (!m_objects.contains(source) || !m_objects.contains(destin))
    {
        return false;
    }

    m_objects[source]->disconnectLink(link);
    m_objects[destin]->disconnectLink(link);

    return true;
}

bool GraphModel::convert(int id, IScaObject::IScaObjectType toType)
{
    ScaObjectConverter converter;

    qDebug() << "[GraphModel]: Converting #" << id << "from type"
             << m_objects[id]->getType() << "to type:" << toType;
    IScaObject *object = converter.convert(m_objects[id], toType);
    if(object == NULL)
    {
        return false;
    }

    replaceObject(object, id);
    return true;
}

void GraphModel::addLinkTo(IScaObject *obj, int link)
{
    obj->addLink(link);
}

bool GraphModel::editAnnotation(int id)
{
    if (id < 0 || !m_objects.contains(id))
        return false;
    bool ok = false;
    QString new_annotation =
            QInputDialog::getText(NULL, EDIT_ANNOTATION,
                                  EDIT_ANNOTATION_LABEL, QLineEdit::Normal,
                                  m_objects[id]->getAnnotation(),
                                  &ok);
    //If user pressed OK then set new annotation
    if (ok == true)
    {
        setAnnotation(id, new_annotation);
    }
    return ok;
}

void GraphModel::setAnnotation(int id, const QString &annotation)
{
    bool showed = m_isShown.value(id, false);
    if (annotation.isEmpty()
        && (showed == false))
    {
        removeObject(id);
    }
    else
    {
        m_objects[id]->setAnnotation(annotation);
    }
    QModelIndex ind = index(id, 0);
    emit dataChanged(ind, ind);
}

void GraphModel::setFilePath(int id, const QString &path)
{
    if (!m_objects.contains(id))
    {
        m_objects[id]->setFile(QFileInfo(path));
    }
}

void GraphModel::clear()
{
    foreach(IScaObject *obj, m_objects)
    {
        removeRow(getId(obj));
    }
    s_nextID = 0;
}
