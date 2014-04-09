/*
 * Copyright 2014    
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

/*!
 * \file GraphFilter_Test.h
 * \brief Test suite for GraphFilter class
 *
 * PROJ: OSLL/sca
 * ----------------------------------------------------------- */


#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>

//include Application class
#include "../src/GraphFilter.h"
#include "../src/GraphModel.h"
#include "../src/ObjectCreator.h"
#include "../src/common/IScaObject.h"

namespace Test
{
    class GraphFilter_Test : public QObject
    {
        Q_OBJECT

        GraphModel *m_tstModel;
        GraphFilter *m_tstObject; // Object for testing
  
    public:
        GraphFilter_Test(QObject *parent = NULL) : QObject(parent)
        {
            m_tstModel = new GraphModel(this);
            m_tstObject = new GraphFilter(m_tstModel, this);
        }
        ~GraphFilter_Test()
        {
            delete m_tstObject;
            delete m_tstModel;
        }
  
    private slots:
        void filtersOk()
        {
            QList<IScaObject::IScaObjectType> types;
            QStringList paths;
            QStringList annotations;
            QStringList content;
            types << IScaObject::DIRECTORY << IScaObject::DIRECTORY << IScaObject::TEXTBLOCK;
            paths << QDir::rootPath()
                  << QDir::rootPath() + "Windows/"
                  << QDir::rootPath() + "text.txt";
            annotations << "Root" << "Windows" << "Text";
            content << "" << "" << "Text";

            QList<int> ids;
            for(int i = 0; i < types.size(); i++)
            {
                IScaObject *object = ObjectCreator::createObject(types[i],
                                            0, 0, 0, 0,
                                            paths[i],
                                            content[i],
                                            QByteArray(),
                                            annotations[i]);
                int id = m_tstModel->addObject(object);
                ids.append(id);
            }

            IScaObjectGroup *group = ObjectCreator::createGroup(ids, m_tstModel);
            int id = m_tstModel->addObject((IScaObject *)(group));
            QModelIndex grIndex = m_tstModel->index(id, 0);

            for (int i = 0; i < paths.size(); i++)
            {
                m_tstObject->setFilePath(paths[i]);
                m_tstObject->setAnnotation(annotations[i]);
                m_tstObject->setContent(content[i]);

                QModelIndex index = m_tstModel->index(i, 0);

                bool accepted = m_tstObject->data(index, highlightRole).toBool();
                QVERIFY(accepted);
                accepted = m_tstObject->data(grIndex, highlightRole).toBool();
                QVERIFY(accepted);
            }

            //Test group on not acception
            QModelIndex index = m_tstModel->index(id, 0);

            m_tstObject->setFilePath("Wrong path");
            bool accepted = m_tstObject->data(index, highlightRole).toBool();
            QVERIFY(!accepted);

            m_tstObject->setAnnotation("Wrong annotation");
            m_tstObject->refreshRegExp();
            accepted = m_tstObject->data(index, highlightRole).toBool();
            QVERIFY(!accepted);

            m_tstObject->setContent("Wrong content");
            m_tstObject->refreshRegExp();
            accepted = m_tstObject->data(index, highlightRole).toBool();
            QVERIFY(!accepted);
            m_tstModel->clear();
        }
    }; // class GraphFilter_Test

} // end of namespace Test
