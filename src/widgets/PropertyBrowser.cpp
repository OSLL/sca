/*
 * Copyright 2014  Leonid Skorospelov  leosko94@gmail.com
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
 * \file PropertyBrowser.cpp
 * \brief PropertyBrowser implementation
 *
 * File description
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include <QDebug>

#include "../StringConstants.h"
#include "PropertyBrowser.h"

#include "../qtpropertybrowser/qtpropertymanager.h"
#include "../qtpropertybrowser/qteditorfactory.h"

#include "../common/IScaObject.h"
#include "../common/IScaObjectFile.h"
#include "../common/IScaObjectTextBlock.h"
#include "../common/IScaObjectDirectory.h"
#include "../common/IScaObjectSymbol.h"
#include "../common/IScaObjectLine.h"
#include "../common/IScaObjectIdentifier.h"
#include "../common/IScaObjectBinaryBlock.h"
#include "../common/Link.h"

#include "../GraphScene.h"
#include "../GraphModel.h"
#include "../visual/ObjectVisual.h"

PropertyBrowser::PropertyBrowser(QWidget *parent)
{
    PropertyBrowser(NULL, NULL, parent);
}

PropertyBrowser::PropertyBrowser(GraphModel *model, GraphScene *scene, QWidget *parent) :
    QtTreePropertyBrowser(parent),
    m_currentId(-1),
    m_model(model),
    m_scene(scene)
{
    m_doubleManager = new QtDoublePropertyManager(this);
    m_stringManager = new QtStringPropertyManager(this);
    m_colorManager = new QtColorPropertyManager(this);
    m_intManager = new QtIntPropertyManager(this);
    m_sizeManager = new QtSizePropertyManager(this);

    connect(m_intManager, SIGNAL(valueChanged(QtProperty *, const int &)),
            this, SLOT(valueChanged(QtProperty *, const int &)));
    connect(m_doubleManager, SIGNAL(valueChanged(QtProperty *, const double &)),
            this, SLOT(valueChanged(QtProperty *, const double &)));
    connect(m_stringManager, SIGNAL(valueChanged(QtProperty *, const QString &)),
            this, SLOT(valueChanged(QtProperty *, const QString &)));
    connect(m_colorManager, SIGNAL(valueChanged(QtProperty *, const QColor &)),
            this, SLOT(valueChanged(QtProperty *, const QColor &)));
    connect(m_sizeManager, SIGNAL(valueChanged(QtProperty *, const QSize &)),
            this, SLOT(valueChanged(QtProperty *, const QSize &)));

    QtDoubleSpinBoxFactory *doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
    QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);

    setFactoryForManager(m_doubleManager, doubleSpinBoxFactory);
    setFactoryForManager(m_stringManager, lineEditFactory);
    setFactoryForManager(m_colorManager->subIntPropertyManager(), spinBoxFactory);
    setFactoryForManager(m_intManager, spinBoxFactory);
    setFactoryForManager(m_sizeManager->subIntPropertyManager(), spinBoxFactory);
}

PropertyBrowser::~PropertyBrowser()
{
}

GraphModel *PropertyBrowser::getModel() const
{
    return m_model;
}

void PropertyBrowser::setModel(GraphModel *model)
{
    m_model = model;
}

GraphScene *PropertyBrowser::getScene() const
{
    return m_scene;
}

void PropertyBrowser::setScene(GraphScene *scene)
{
    m_scene = scene;
}

void PropertyBrowser::updateExpandState()
{
    QList<QtBrowserItem *> list = QtTreePropertyBrowser::topLevelItems();
    QListIterator<QtBrowserItem *> it(list);
    while (it.hasNext())
    {
        QtBrowserItem *item = it.next();
        QtProperty *prop = item->property();
        m_idToExpanded[m_propertyToId[prop]] = QtTreePropertyBrowser::isExpanded(item);
    }
}

void PropertyBrowser::resetState()
{
    //Just delete everything from containers
    QMap<QtProperty *, QString>::ConstIterator itProp = m_propertyToId.constBegin();
    while (itProp != m_propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }

    m_idToProperty.clear();
    m_propertyToId.clear();
}

void PropertyBrowser::processObject(IScaObject *object)
{
    QtProperty *property;

    property = m_stringManager->addProperty(PROPERTY_TYPE);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, object->getTypeName());
    addProperty(property, PROPERTY_TYPE);

    if (object->getType() != IScaObject::LINK)
    {
        property = m_stringManager->addProperty(PROPERTY_FILEPATH);
        m_stringManager->setValue(property, object->getFile().absoluteFilePath());
        addProperty(property, PROPERTY_FILEPATH);
    }

    property = m_stringManager->addProperty(PROPERTY_ANNOTATION);
    m_stringManager->setValue(property, object->getAnnotation());
    addProperty(property, PROPERTY_ANNOTATION);

    switch (object->getType())
    {
    case IScaObject::BINARYBLOCK:
        processBinaryBlock(static_cast<IScaObjectBinaryBlock *>(object));
        break;
    case IScaObject::IDENTIFIER:
        processIdentifier(static_cast<IScaObjectIdentifier *>(object));
        break;
    case IScaObject::TEXTBLOCK:
        processTextBlock(static_cast<IScaObjectTextBlock *>(object));
        break;
    case IScaObject::SYMBOL:
        processSymbol(static_cast<IScaObjectSymbol *>(object));
        break;
    case IScaObject::LINE:
        processLine(static_cast<IScaObjectLine *>(object));
        break;
    case IScaObject::LINK:
        processLink(static_cast<Link *>(object));
        break;
    default:
        qDebug() << "[PropertyManager]: unknown type while processing, " << object->getType();
        break;
    }
}

void PropertyBrowser::processBinaryBlock(IScaObjectBinaryBlock *object)
{
    QtProperty *property;

    property = m_intManager->addProperty(PROPERTY_LENGTH);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getLength());
    addProperty(property, PROPERTY_LENGTH);

    property = m_intManager->addProperty(PROPERTY_OFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getOffset());
    addProperty(property, PROPERTY_OFFSET);

    property = m_stringManager->addProperty(PROPERTY_DATA);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, object->getReadableData());
    addProperty(property, PROPERTY_DATA);
}

void PropertyBrowser::processIdentifier(IScaObjectIdentifier *object)
{
    QtProperty *property;

    property = m_intManager->addProperty(PROPERTY_LENGTH);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getIdentifier().length());
    addProperty(property, PROPERTY_LENGTH);

    property = m_intManager->addProperty(PROPERTY_OFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getOffset());
    addProperty(property, PROPERTY_OFFSET);

    property = m_intManager->addProperty(PROPERTY_ENDOFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getEndOffset());
    addProperty(property, PROPERTY_ENDOFFSET);

    property = m_stringManager->addProperty(PROPERTY_IDENTIFIER);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, object->getIdentifier());
    addProperty(property, PROPERTY_IDENTIFIER);
}

void PropertyBrowser::processTextBlock(IScaObjectTextBlock *object)
{
    QtProperty *property;

    property = m_intManager->addProperty(PROPERTY_LENGTH);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getLength());
    addProperty(property, PROPERTY_LENGTH);

    property = m_intManager->addProperty(PROPERTY_OFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getOffset());
    addProperty(property, PROPERTY_OFFSET);

    property = m_intManager->addProperty(PROPERTY_ENDOFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getEndOffset());
    addProperty(property, PROPERTY_ENDOFFSET);

    property = m_stringManager->addProperty(PROPERTY_TEXT);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, object->getText());
    addProperty(property, PROPERTY_TEXT);
}

void PropertyBrowser::processSymbol(IScaObjectSymbol *object)
{
    QtProperty *property;

    property = m_intManager->addProperty(PROPERTY_OFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getOffset());
    addProperty(property, PROPERTY_OFFSET);

    property = m_stringManager->addProperty(PROPERTY_SYMBOL);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, QString(object->getSymbol()));
    addProperty(property, PROPERTY_SYMBOL);
}

void PropertyBrowser::processLine(IScaObjectLine *object)
{
    QtProperty *property;

    property = m_intManager->addProperty(PROPERTY_OFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getOffset());
    addProperty(property, PROPERTY_OFFSET);

    property = m_intManager->addProperty(PROPERTY_ENDOFFSET);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getEndOffset());
    addProperty(property, PROPERTY_ENDOFFSET);

    property = m_intManager->addProperty(PROPERTY_LINE_NUMBER);
    m_intManager->setReadOnly(property, true);
    m_intManager->setValue(property, object->getLineNumber());
    addProperty(property, PROPERTY_LINE_NUMBER);

    property = m_stringManager->addProperty(PROPERTY_LINE);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, object->getLine());
    addProperty(property, PROPERTY_LINE);
}

void PropertyBrowser::processLink(Link *object)
{
    QtProperty *property;

    int fromId = object->getObjectFrom(),
        toId = object->getObjectTo();
    IScaObject *from = m_model->getObjectById(fromId),
               *to = m_model->getObjectById(toId);
    Q_ASSERT(from != NULL && to != NULL);

    property = m_stringManager->addProperty(PROPERTY_OBJECT_FROM);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, from->getInfo());
    addProperty(property, PROPERTY_OBJECT_FROM);

    property = m_stringManager->addProperty(PROPERTY_OBJECT_TO);
    m_stringManager->setReadOnly(property, true);
    m_stringManager->setValue(property, to->getInfo());
    addProperty(property, PROPERTY_OBJECT_TO);
}

void PropertyBrowser::processVisualObject(ObjectVisual *object)
{
    QtProperty *property;
    ObjectVisual::ObjectVisualType type = object->getType();
    bool objIsLink = (type == ObjectVisual::LINK);

    property = m_doubleManager->addProperty(PROPERTY_POSITION_X);
    m_doubleManager->setValue(property, object->pos().x());
    if (objIsLink)
    {
        m_doubleManager->setReadOnly(property, true);
    }
    m_doubleManager->setRange(property, 0, m_scene->width());
    addProperty(property, PROPERTY_POSITION_X);

    property = m_doubleManager->addProperty(PROPERTY_POSITION_Y);
    m_doubleManager->setValue(property, object->pos().y());
    if (objIsLink)
    {
        m_doubleManager->setReadOnly(property, true);
    }
    m_doubleManager->setRange(property, 0, m_scene->height());
    addProperty(property, PROPERTY_POSITION_Y);

    property = m_colorManager->addProperty(PROPERTY_COLOR);
    m_colorManager->setValue(property, object->getStandardColor());
    addProperty(property, PROPERTY_COLOR);

    if (!objIsLink)
    {
        Node *node = static_cast<Node *>(object);
        property = m_sizeManager->addProperty(PROPERTY_SIZE);
        m_sizeManager->setValue(property, node->boundingRect().size().toSize());
        addProperty(property, PROPERTY_SIZE);
    }
}

void PropertyBrowser::addProperty(QtProperty *property, const QString &id)
{
    m_propertyToId[property] = id;
    m_idToProperty[id] = property;
    QtBrowserItem *item = QtTreePropertyBrowser::addProperty(property);
    if (m_idToExpanded.contains(id))
        QtTreePropertyBrowser::setExpanded(item, m_idToExpanded[id]);
}

void PropertyBrowser::loadItem(int id)
{
    updateExpandState();
    //Clean up old state
    resetState();

    if (id < 0)
        return;
    //Get object by it's id
    IScaObject *object = m_model->getObjectById(id);
    if (object == NULL)
    {
        qDebug() << "[PropertyManager]: can't get object from model!";
        return;
    }

    ObjectVisual *visObj = m_scene->getObjectById(id);
    if (visObj == NULL)
    {
        qDebug() << "[PropertyManager]: can't cast object from scene!";
        return;
        // no return if sometime we wish to see object with no graphics
    }

    m_currentId = id;
    processObject(object);
    processVisualObject(visObj);
}

void PropertyBrowser::itemMoved(int id)
{
    if (m_currentId != id)
    {
        loadItem(id);
    }
    ObjectVisual *objVis = m_scene->getObjectById(id);
    if (objVis == NULL)
        return;
    QtProperty *property;

    property = m_idToProperty[PROPERTY_POSITION_X];
    m_doubleManager->setValue(property, objVis->pos().x());

    property = m_idToProperty[PROPERTY_POSITION_Y];
    m_doubleManager->setValue(property, objVis->pos().y());
}

void PropertyBrowser::valueChanged(QtProperty *property, const int &value)
{
    Q_UNUSED(property);
    Q_UNUSED(value);
    //nothing possible to change
}

void PropertyBrowser::valueChanged(QtProperty *property, const QSize &value)
{
    if (!m_propertyToId.contains(property))
        return;

    ObjectVisual *visObj = m_scene->getObjectById(m_currentId);
    Node *node = static_cast<Node *>(visObj);

    QString id = m_propertyToId[property];
    if (id == PROPERTY_SIZE)
    {
        node->setSize(value);
    }
    m_scene->update();
}

void PropertyBrowser::valueChanged(QtProperty *property, const double &value)
{
    if (!m_propertyToId.contains(property))
        return;

    ObjectVisual *visObj = m_scene->getObjectById(m_currentId);
    if (visObj == NULL)
        return;

    QString id = m_propertyToId[property];
    if (id == PROPERTY_POSITION_X)
    {
        visObj->setX(value);
    }
    else if (id == PROPERTY_POSITION_Y)
    {
        visObj->setY(value);
    }
    m_scene->update();
}

void PropertyBrowser::valueChanged(QtProperty *property, const QString &value)
{
    if (!m_propertyToId.contains(property))
        return;

    QString id = m_propertyToId[property];
    if (id == PROPERTY_ANNOTATION)
    {
        m_model->setAnnotation(m_currentId, value);
    }
    else if (id == PROPERTY_FILEPATH)
    {
        m_model->setFilePath(m_currentId, value);
    }
    m_scene->update();
}

void PropertyBrowser::valueChanged(QtProperty *property, const QColor &value)
{
    if (!m_propertyToId.contains(property))
        return;

    ObjectVisual *visObj;
    visObj = m_scene->getObjectById(m_currentId);
    QString id = m_propertyToId[property];
    if (id == PROPERTY_COLOR)
    {
        visObj->setStandardColor(value);
    }
    m_scene->update(visObj->boundingRect());
}
