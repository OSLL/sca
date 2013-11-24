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
#include "common/ScaObjectConverter.h"

//ID = 0 for objects, which doesn't exist in model
quint32 GraphModel::s_nextID = 1;

GraphModel::GraphModel() :
    QAbstractListModel()
{

}

GraphModel::~GraphModel()
{

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
    qDebug() << "Connecting " << *source << " with " << *dest;
    Link *res = new Link(source, dest);
    source->addLink(res);
    dest->addLink(res);
    QModelIndex changedIndex = createIndex(0, 0, s_nextID);
    setData(changedIndex, QVariant::fromValue(res));

    return s_nextID++;
}

void GraphModel::disconnectObjects(quint32 id1, quint32 id2, Link *link)
{
    if (id1 == 0 || id2 == 0)
    {
        qDebug() << "Nodes no more exist";
        return;
    }
    m_objects[id1]->disconnectLink(link);
    m_objects[id2]->disconnectLink(link);

    QModelIndex sourceIndex = createIndex(0, 0, id1);
    QModelIndex destinIndex = createIndex(0, 0, id2);

    emit dataChanged(sourceIndex, sourceIndex);
    emit dataChanged(destinIndex, destinIndex);
}

void GraphModel::disconnectObjects(IScaObject *source, IScaObject *dest, Link *link)
{
    if(source == NULL || dest == NULL || link == NULL)
    {
        return;
    }

    quint32 sourceId = m_objects.key(source);
    quint32 destinId = m_objects.key(dest);

    return disconnectObjects(sourceId, destinId, link);
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
    qDebug() << "AddObject()";
    QModelIndex changedIndex = createIndex(0, 0, s_nextID);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return s_nextID++;
}

quint32 GraphModel::replaceObject(IScaObject *object, quint32 id)
{
    delete(m_objects[id]);
    m_objects[id] = NULL;

    qDebug() << "AddObject()";
    QModelIndex changedIndex = createIndex(0, 0, id);
    setData(changedIndex, QVariant::fromValue(object), Qt::DecorationRole);

    return id;
}

quint32 GraphModel::getId(IScaObject *object)
{
    return m_objects.key(object);
}

QVariant GraphModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "Data called for #" << index.internalId();
    if (!m_objects.contains(index.internalId()))
        return QVariant();
    switch (role)
    {
    case Qt::DisplayRole:
    {
        return QVariant(m_objects[index.internalId()]->getAnnotation());
    }
    case Qt::DecorationRole:
    {
        IScaObject *object = m_objects[index.internalId()];
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
    beginRemoveRows(parent, id, id);
    IScaObject *object = m_objects.take(id);

    if(object == NULL)
    {
        qDebug() << "Object does't exist";
        return false;
    }

    if(object->getType() == IScaObject::LINK)
    {
        Link *link = static_cast<Link *>(object);
        removeLink(link);
    }

    foreach(Link *link, object->getLinks())
    {
        removeObject(link);
    }
    delete object;

    qDebug() << "Removed: ID = " << id;
    endRemoveRows();

    return true;
}

bool GraphModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!m_objects.contains(row))
    {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        m_objects.remove(row + i);
    }
    endRemoveRows();
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
    if (value.isNull())
        return false;
    if (index.internalId() < 0)
        return false;
    switch (role)
    {
    case Qt::DecorationRole:
    {
        IScaObject *object = NULL;
        //Try casting to object or link, then add it
        object = qvariant_cast<IScaObject *>(value);
        if (object == NULL)
        {
            object = qvariant_cast<Link *>(value);
            if (object == NULL)
            {
                qDebug() << "Can\'t cast object!";
                return false;
            }
        }
        qDebug() << "Added element #" << s_nextID << ", type: " << object->getType();
        m_objects.insert(index.internalId(), object);
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
    return removeRow(id, QModelIndex());
}

bool GraphModel::removeObject(IScaObject *obj)
{
    quint32 key = m_objects.key(obj);
    if(m_objects.contains(key))
        return removeObject(key);
    else
        return false;
}

bool GraphModel::removeLink(Link *link)
{
    if(link == NULL)
    {
        return false;
    }

    IScaObject *source = link->getObjectFrom();
    IScaObject *destin = link->getObjectTo();

    if(source == NULL || destin == NULL)
    {
        return false;
    }

    disconnectObjects(source, destin, link);

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

void GraphModel::setAnnotation(quint32 id, QString annotation)
{
    Link *link = static_cast<Link *>(m_objects[id]);
    Q_ASSERT(link != NULL);
    link->setAnnotation(annotation);
    QModelIndex index = createIndex(0, 0, id);
    emit dataChanged(index, index);
}

