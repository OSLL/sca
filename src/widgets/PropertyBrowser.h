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
 * \file PropertyBrowser.h
 * \brief Header of PropertyBrowser
 * \todo add comment here
 *
 * class for browsing object's properties
 *
 * PROJ: OSLL/sca
 * ---------------------------------------------------------------- */

#include <QMap>
#include "../qtpropertybrowser/qttreepropertybrowser.h"
class IScaObject;
class IScaObjectTextBlock;
class IScaObjectLine;
class IScaObjectSymbol;
class IScaObjectIdentifier;
class IScaObjectBinaryBlock;
class Link;
class QtDoublePropertyManager;
class QtStringPropertyManager;
class QtColorPropertyManager;
class QtIntPropertyManager;
class QtSizePropertyManager;
class ObjectVisual;
class GraphModel;
class GraphScene;

#ifndef _PropertyBrowser_H_1737E12F_0ED0_4E09_AB8C_FE958CBC48F1_INCLUDED_
#define _PropertyBrowser_H_1737E12F_0ED0_4E09_AB8C_FE958CBC48F1_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 * Class provides viewing IScaObjects in PropertyBrowser
 * Lots of code copied from example canvas_typed in QtPropertyBrowser framework package
 *
 */
class PropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    PropertyBrowser(QWidget *parent = 0);
    PropertyBrowser(GraphModel *model, GraphScene *scene, QWidget *parent = 0);

    virtual ~PropertyBrowser();

    GraphModel *getModel() const;
    void setModel(GraphModel *model);

    GraphScene *getScene() const;
    void setScene(GraphScene *scene);

private:
    int m_currentId;
    GraphModel *m_model;
    GraphScene *m_scene;

    void addProperty(QtProperty *property, const QString &id);
    void updateExpandState();
    void resetState();
    void processObject(IScaObject *object);
    void processBinaryBlock(IScaObjectBinaryBlock *object);
    void processIdentifier(IScaObjectIdentifier *object);
    void processTextBlock(IScaObjectTextBlock *object);
    void processSymbol(IScaObjectSymbol *object);
    void processLine(IScaObjectLine *object);
    void processLink(Link *object);
    void processVisualObject(ObjectVisual *object);

    QMap<QtProperty *, QString> m_propertyToId;
    QMap<QString, QtProperty *> m_idToProperty;
    QMap<QString, bool> m_idToExpanded;

    QtDoublePropertyManager *m_doubleManager;
    QtStringPropertyManager *m_stringManager;
    QtColorPropertyManager *m_colorManager;
    QtIntPropertyManager *m_intManager;
    QtSizePropertyManager *m_sizeManager;
public slots:
    void loadItem(int id);
    void itemMoved(int id);
    void valueChanged(QtProperty *property, const double &value);
    void valueChanged(QtProperty *property, const QString &value);
    void valueChanged(QtProperty *property, const QColor &value);
    void valueChanged(QtProperty *property, const int &value);
    void valueChanged(QtProperty *property, const QSize &value);
}; // class PropertyBrowser


#endif //_PropertyBrowser_H_1737E12F_0ED0_4E09_AB8C_FE958CBC48F1_INCLUDED_

