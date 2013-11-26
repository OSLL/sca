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
#include "common/ScaObjectConverter.h"
#include "StringConstants.h"

//ID = 0 for objects, which doesn't exist in model
quint32 GraphModel::s_nextID = 1;

GraphModel::GraphModel() :
    QAbstractListModel()
{

}

GraphModel::~GraphModel()
{
    foreach(IScaObject *obj, m_objects)
    {
        removeRow(getId(obj));
    }
}

quint32 GraphModel::connectObjects(quint32 id1, quint32 id2)
{
    if (!m_objects.contains(id1) || !m_objects.contains(id2))
    {
        return 0;
    }
    return connectObjects(m_objects[id1], m_objects[id2]);
}

quint32 GraphModel::connectObjects(IScaObject *source, IScaObject *dest)
{
    qDebug() << "Connecting " << *source << " to " << *dest;
    Link *link = new Link(source, dest);
    source->addLink(link);
    dest->addLink(link);
    QModelIndex linkIndex = index(s_nextID);
    if (!setData(linkIndex, QVariant::fromValue(link)))
    {
        qDebug() << "Couldn\'t set data in model.";
    }

    return s_nextID++;
}

quint32 GraphModel::addObject(const QMimeData *mimeData)
{
    if (!mimeData->hasUrls())
    {
        return -1;
    }

    ScaMIMEDataProcessor processor(mimeData);
    IScaObject *object = processor.makeObject();
    return addObject(object);
}

quint32 GraphModel::addObject(IScaObject *object)
{
    qDebug() << "";
    QModelIndex changedIndex = index(s_nextID);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return s_nextID++;
}

quint32 GraphModel::replaceObject(IScaObject *object, quint32 id)
{
    delete(m_objects[id]);
    m_objects[id] = NULL;

    QModelIndex changedIndex = createIndex(0, 0, id);
    setData(changedIndex, QVariant::fromValue(object));

    return id;
}

quint32 GraphModel::getId(IScaObject *object)
{
    return m_objects.key(object);
}

QModelIndex GraphModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column, row);
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    quintptr id = index.internalId();
    qDebug() << "Data called for #" << id;
    if (!m_objects.contains(id))
    {
        qDebug() << "Model doesn\'t have this object.";
        return QVariant();
    }
    switch (role)
    {
    case Qt::DisplayRole:   //For standart text views
        {
            return QVariant(m_objects[id]->getAnnotation());
        }
    case Qt::DecorationRole:    //For graphics representation return full object
        {
            IScaObject *object = m_objects[id];
            if (object->getType() == IScaObject::LINK)
            {
                Link *link = static_cast<Link *>(object);
                return QVariant::fromValue(link);
            }
            return QVariant::fromValue(object);
        }
    default:
        {
            return QVariant();
        }
    }
}

Qt::ItemFlags GraphModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool GraphModel::removeRow(quint32 id, const QModelIndex &parent)
{
    IScaObject *object = m_objects.value(id, NULL);

    if (object == NULL)
    {
        qDebug() << "Object doesn\'t exist";
        return false;
    }

    //Remove connections in model of that object first (recursively)
    foreach(Link *link, object->getLinks())
    {
        removeObject(link);
    }

    //Start removing object itself
    beginRemoveRows(parent, id, id);

    if (object->getType() == IScaObject::LINK)
    {
        //Disconnect it from source and destination
        Link *l = static_cast<Link *>(object);
        qDebug() << "Freeing link #" << getId(l);
        freeLink(l);
    }

    //Remove it from memory
    delete object;

    m_objects.remove(id);
    qDebug() << "Removed: ID = " << id << " from model. Items left: " << m_objects.size();
    endRemoveRows();

    return true;
}

bool GraphModel::removeRows(int row, int count, const QModelIndex &parent)
{
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
    qDebug() << "Objects: " << m_objects.size();
    return m_objects.size();
}

bool GraphModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //First check if it is valid index given
    if (value.isNull())
    {
        return false;
    }
    if (index.internalId() <= 0)
    {
        return false;
    }

    switch (role)
    {
    case Qt::DecorationRole:
        {
            quint32 id = index.internalId();
            IScaObject *object = NULL;

            //Try casting to object or link, then add it
            object = qvariant_cast<IScaObject *>(value);
            if (object == NULL)
            {
                object = qvariant_cast<Link *>(value);
                if (object == NULL)
                {
                    qDebug() << "Can\'t cast object while adding to model!";
                    return false;
                }
            }

            //Successfully casted
            //Set new data (or replace it)
            m_objects.insert(id, object);
            qDebug() << "Added #" << s_nextID << ", type: " << object->getType()
                     << ", items: " << m_objects.size();
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
bool GraphModel::removeObject(quint32 id)
{
    return removeRow(id);
}

bool GraphModel::removeObject(IScaObject *obj)
{
    quint32 id = m_objects.key(obj);
    return removeObject(id);
}

bool GraphModel::freeLink(Link *link)
{
    if (link == NULL)
    {
        return false;
    }

    IScaObject *source = link->getObjectFrom();
    IScaObject *destin = link->getObjectTo();

    if (source == NULL || destin == NULL)
    {
        return false;
    }

    source->disconnectLink(link);
    source->disconnectLink(link);

    return true;
}

bool GraphModel::convert(quint32 id, IScaObject::IScaObjectType toType)
{
    ScaObjectConverter *converter = new ScaObjectConverter();

    qDebug() << "Converting #" << id << " to type: " << toType;
    IScaObject *object = converter->convert(m_objects[id], toType);
    if(object == NULL)
    {
        return false;
    }

    replaceObject(object, id);
    return true;
}

void GraphModel::addLinkTo(IScaObject *obj, Link *link)
{
    obj->addLink(link);
}

void GraphModel::editLinkAnnotation(quint32 id)
{
    if (id <= 0 || !m_objects.contains(id))
        return;
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
}

void GraphModel::setAnnotation(quint32 id, QString annotation)
{
    Link *link = static_cast<Link *>(m_objects[id]);
    Q_ASSERT(link != NULL);
    link->setAnnotation(annotation);
    QModelIndex ind = index(id);
    emit dataChanged(ind, ind);
}

