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

/*!
 * \file IScaObjectGroup_Test.h
 * \brief Test suite for IScaObjectGroup class
 *
 * PROJ: OSLL/sca
 * ----------------------------------------------------------- */


#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QString>

//include Application class
#include "../src/GraphModel.h"
#include "../src/GraphScene.h"
#include "../src/ObjectCreator.h"

const QString LONG_GROUP_NAME  = "123456789012345678901234567890";
const QString SHORT_GROUP_NAME = LONG_GROUP_NAME.mid(0, 15) + "...";

namespace Test
{
    class IScaObjectGroup_Test : public QObject
    {
        Q_OBJECT

        GraphModel *m_tstModel;
        GraphScene *m_tstScene;
  
    public:
        IScaObjectGroup_Test(QObject *parent = NULL) : QObject(parent)
        {
            m_tstModel = new GraphModel(this);
            m_tstScene = new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT, this);
            m_tstScene->setModel(m_tstModel);

            connect(m_tstModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                    m_tstScene, SLOT(updateObjects(QModelIndex, QModelIndex)));
            connect(m_tstModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                    m_tstScene, SLOT(removeObject(QModelIndex,int,int)));
        }
        ~IScaObjectGroup_Test()
        {
            m_tstModel = NULL;
            m_tstScene = NULL;
        }
  
    private slots:
        void isSceneWorks()
        {
            //Create simple dir-like object
            QMimeData mime;
            mime.setData(FROM_PATH, QDir::currentPath().toUtf8());
            int objId = m_tstModel->addObject(&mime);
            IScaObject *obj = m_tstModel->getObjectById(objId);
            QVERIFY(obj->getType() == IScaObject::DIRECTORY);
            QVERIFY(objId == 0);
            ObjectVisual *vis = m_tstScene->getObjectById(objId);
            QVERIFY(vis != NULL);
            QVERIFY(vis->getType() == ObjectVisual::NODE);
            m_tstModel->removeObject(objId);
            vis = m_tstScene->getObjectById(objId);
            QVERIFY(vis == NULL);
            m_tstModel->clear();
            m_tstScene->clear();
        }
        void canSceneConnect()
        {
            QMimeData *mime = new QMimeData();
            mime->setData(FROM_PATH, QDir::currentPath().toUtf8());
            int obj1 = m_tstModel->addObject(mime),
                obj2 = m_tstModel->addObject(mime);
            QVERIFY(obj1 == 0);
            QVERIFY(obj2 == 1);
            int link = m_tstModel->connectObjects(obj1, obj2);
            QVERIFY(link == 2);
            ObjectVisual *visLink = m_tstScene->getObjectById(link);
            QVERIFY(visLink != NULL);
            QVERIFY(visLink->getType() == ObjectVisual::LINK);
            ObjectVisual *vis1 = m_tstScene->getObjectById(obj1),
                         *vis2 = m_tstScene->getObjectById(obj2);
            QVERIFY(vis1 != NULL);
            QVERIFY(vis2 != NULL);
            QVERIFY(vis1->getType() == ObjectVisual::NODE);
            QVERIFY(vis2->getType() == ObjectVisual::NODE);
            QVERIFY(vis1->getLinks().size() == 1);
            QVERIFY(vis2->getLinks().size() == 1);
            m_tstModel->clear();
            m_tstScene->clear();
        }
        void canSceneAddGroup()
        {
            QMimeData *mime = new QMimeData();
            mime->setData(FROM_PATH, QDir::currentPath().toUtf8());
            int objId1 = m_tstModel->addObject(mime),
                objId2 = m_tstModel->addObject(mime);
            QCOMPARE(objId1, 0);
            QCOMPARE(objId2, 1);
            QList<int> ids;
            ids << 0 << 1;

            ObjectVisual *vis1 = m_tstScene->getObjectById(objId1),
                         *vis2 = m_tstScene->getObjectById(objId2);
            vis1->setPos(2, 2);
            vis2->setPos(0, 0);
            QVERIFY(vis1 != NULL);
            QVERIFY(vis1->isVisible() == true);
            QVERIFY(vis2 != NULL);
            QVERIFY(vis2->isVisible() == true);

            IScaObjectGroup *group = static_cast<IScaObjectGroup*>(ObjectCreator::createGroup(ids, m_tstModel));
            int groupId = m_tstModel->addObject(group, -1, true);
            ObjectVisual *visGroup = m_tstScene->getObjectById(groupId);
            //Old objects should have disappeared
            QVERIFY(vis1->isVisible() == false);
            QVERIFY(vis2->isVisible() == false);
            QVERIFY(visGroup->pos() == QPointF(1, 1));
            QCOMPARE(groupId, 2);
            QVERIFY(visGroup != NULL);
            QVERIFY(visGroup->getStandardColor() == DEFAULT_GROUP_COLOR);
            m_tstModel->clear();
            m_tstScene->clear();
        }
        void isTitleOk()
        {
            // Init simple group in program
            QMimeData *mime = new QMimeData();
            mime->setData(FROM_PATH, QDir::currentPath().toUtf8());
            int objId1 = m_tstModel->addObject(mime),
                objId2 = m_tstModel->addObject(mime);
            QList<int> ids;
            ids << objId1 << objId2;

            IScaObjectGroup *group = static_cast<IScaObjectGroup*>(ObjectCreator::createGroup(ids, m_tstModel));
            group->setTitle(LONG_GROUP_NAME);
            int groupId = m_tstModel->addObject(group, -1, true);
            IScaObjectGroupVisual *visGroup = static_cast<IScaObjectGroupVisual *>(m_tstScene->getObjectById(groupId));

            QCOMPARE(group->getTitle().compare(LONG_GROUP_NAME), 0);
            QCOMPARE(visGroup->getTitleText().compare(SHORT_GROUP_NAME), 0);

            m_tstModel->clear();
            m_tstScene->clear();
        }
    }; // class IScaObjectGroup_Test

} // end of namespace Test
