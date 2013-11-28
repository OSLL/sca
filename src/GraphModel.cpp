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

GraphModel::GraphModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

GraphModel::~GraphModel()
{
    foreach(IScaObject *obj, m_objects)
    {
        removeRow(getId(obj));
    }
}

quint32 GraphModel::connectObjects(quint32 source, quint32 dest)
{
    //qDebug() << "Connecting " << source << " to " << dest;
    Link *link = new Link(source, dest);
    QModelIndex linkIndex = index(s_nextID);
    m_objects[source]->addLink(s_nextID);
    m_objects[dest]->addLink(s_nextID);
    if (!setData(linkIndex, QVariant::fromValue(link), Qt::DecorationRole))
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
    QModelIndex changedIndex = index(s_nextID);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return s_nextID++;
}

quint32 GraphModel::replaceObject(IScaObject *object, quint32 id)
{
    IScaObject *old = m_objects.value(id, NULL);
    if (old == NULL)
    {
        qDebug() << "Object didn't exist before converting!";
    }
    QList<quint32> links = old->getLinks();  //Save links
    delete old;
    m_objects[id] = NULL;
    object->setLinks(links);    //Restore links

    QModelIndex changedIndex = index(id);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return id;
}

quint32 GraphModel::getId(IScaObject *object)
{
    quint32 id = m_objects.key(object);
    //qDebug() << "Requsted id" << id << "in model";
    return id;
}

QModelIndex GraphModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column, row);
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    quintptr id = index.internalId();
    if (index.internalId() <= 0)
    {
        return QVariant();
    }
    //qDebug() << "Data called for #" << id << "(" << *(m_objects.value(id, NULL)) << ")";
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
    case Qt::ToolTipRole:
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

bool GraphModel::removeRow(quint32 id, const QModelIndex &parent)
{
    IScaObject *object = m_objects.value(id, NULL);

    if (object == NULL)
    {
        qDebug() << "Object doesn\'t exist";
        return false;
    }

    //Remove connections in model of that object first (recursively)
    qDebug() << "Removing " << object->getLinks().size() << " links of #" << id << "first.";
    foreach(quint32 link, object->getLinks())
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

    //Remove it from memory
    delete object;
    //Remove from container
    m_objects.remove(id);

    qDebug() << "Removed: ID = " << id << " from model. Items left: " << m_objects.size();
    endRemoveRows();

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
    qDebug() << "Objects: " << m_objects.size();
    return m_objects.size();
}

bool GraphModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //First check if it is valid parameters given
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
            qDebug() << "Data set #" << id << ", type: " << object->getType()
                     << ", items total: " << m_objects.size();
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

bool GraphModel::freeLink(quint32 link)
{
    if (m_objects[link]->getType() != IScaObject::LINK)
    {
        return false;
    }

    Link *l = static_cast<Link *>(m_objects[link]);
    quint32 source = l->getObjectFrom();
    quint32 destin = l->getObjectTo();

    qDebug() << "Freeing link #" << link << "("
             << source << ";" << destin << ")";
    if (!m_objects.contains(source) || !m_objects.contains(destin))
    {
        return false;
    }

    m_objects[source]->disconnectLink(link);
    m_objects[destin]->disconnectLink(link);

    return true;
}

bool GraphModel::convert(quint32 id, IScaObject::IScaObjectType toType)
{
    ScaObjectConverter *converter = new ScaObjectConverter();

    qDebug() << "Converting #" << id << "from type"
             << m_objects[id]->getType() << "to type:" << toType;
    IScaObject *object = converter->convert(m_objects[id], toType);
    if(object == NULL)
    {
        return false;
    }

    replaceObject(object, id);
    return true;
}

void GraphModel::addLinkTo(IScaObject *obj, quint32 link)
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
    m_objects[id]->setAnnotation(annotation);
    QModelIndex ind = index(id);
    emit dataChanged(ind, ind);
}
