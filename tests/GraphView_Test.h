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
 * \file GraphView_Test.h
 * \brief Test suite for GraphView class
 *
 * PROJ: OSLL/sca
 * ----------------------------------------------------------- */


#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>

//include Application class
#include "../src/widgets/GraphView.h"
#include "../src/GraphModel.h"

const int TEST_OBJECTS_COUNT = 5;
// should be counted manually
const int GROUP_OBJECTS_COUNT = 2;
const QPointF TEST_POSITIONS[] = {
    QPointF(-2,2),
    QPointF(-1,1),
    QPointF(0,0),
    QPointF(1,1),
    QPointF(2,-2)
};

namespace Test
{
    class GraphView_Test : public QObject
    {
        Q_OBJECT

        GraphView *m_tstView; // Object for testing
        GraphScene *m_tstScene;
        GraphModel *m_tstModel;

    public:
        GraphView_Test(QObject *parent = NULL) : QObject(parent),
            m_tstScene(new GraphScene(0, 0, DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT, this)),
            m_tstModel(new GraphModel)
        {
            // initialization here
            m_tstScene->setModel(m_tstModel);
            connect(m_tstModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                    m_tstScene, SLOT(updateObjects(QModelIndex, QModelIndex)));
            connect(m_tstModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)),
                    m_tstScene, SLOT(removeObject(QModelIndex,int,int)));
            m_tstView = new GraphView();
            m_tstView->setScene(m_tstScene);
            m_tstView->setModel(m_tstModel);
        }
        ~GraphView_Test()
        {
            // destroying  here
            // delete m_tstObject;
            // m_tstObject = NULL;
        }

    private:
        void clear()
        {
            m_tstModel->clear();
            m_tstScene->clear();
        }

    private slots:
        void canCorrectlyWorkWithGroup()
        {
            if (TEST_OBJECTS_COUNT < 4 || GROUP_OBJECTS_COUNT < 2)
            {
                QWARN("Not enough objects specified!");
                clear();
                return;
            }

            QMimeData *mime = new QMimeData();
            mime->setData(FROM_PATH, QDir::currentPath().toUtf8());

            int objs[TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT];
            ObjectVisual *vis[TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT];
            for (int i = 0; i < TEST_OBJECTS_COUNT; i++)
            {
                objs[i] = m_tstModel->addObject(mime);
                vis[i] = m_tstScene->getObjectById(objs[i]);
            }
            // objects' id are [0..TEST_OBJECTS_COUNT-1]

            vis[0]->setSelected(true);
            vis[0]->setPos(TEST_POSITIONS[0]);
            vis[1]->setSelected(true);
            vis[1]->setPos(TEST_POSITIONS[4]);
            m_tstView->createGroupFromSelection();
            // check if after creating group visibility is correct
            int groupId = TEST_OBJECTS_COUNT;
            objs[TEST_OBJECTS_COUNT] = groupId;

            QVERIFY(vis[0]->isVisible() == false);
            QVERIFY(vis[1]->isVisible() == false);
            QVERIFY(vis[0]->pos() == TEST_POSITIONS[0]);
            QVERIFY(vis[1]->pos() == TEST_POSITIONS[4]);

            IScaObject *group = m_tstModel->getObjectById(groupId);
            QVERIFY(group != NULL);
            QVERIFY(group->getType() == IScaObject::GROUP);
            ObjectVisual *objVis = m_tstScene->getObjectById(groupId);
            IScaObjectGroupVisual *grVis = static_cast<IScaObjectGroupVisual *>(objVis);
            QVERIFY(grVis != NULL);
            QVERIFY(grVis->isVisible() == true);
            QVERIFY(grVis->isSelected() == true);
            QVERIFY(grVis->pos() == TEST_POSITIONS[2]);

            m_tstScene->clearSelection();
            clear();
        }
        void removeWorksCorrectlyForGroups()
        {
            if (TEST_OBJECTS_COUNT < 5 || GROUP_OBJECTS_COUNT < 2)
            {
                QWARN("Not enough objects specified!");
                clear();
                return;
            }
            QMimeData *mime = new QMimeData();
            mime->setData(FROM_PATH, QDir::currentPath().toUtf8());

            int ids[TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT];
            IScaObject *objs[TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT];
            ObjectVisual *visObj[TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT];
            for (int i = 0; i < TEST_OBJECTS_COUNT; i++)
            {
                ids[i] = m_tstModel->addObject(mime);
                objs[i] = m_tstModel->getObjectById(ids[i]);
                visObj[i] = m_tstScene->getObjectById(ids[i]);
            }

            // Create group to test removing
            visObj[0]->setSelected(true);
            visObj[1]->setSelected(true);
            m_tstView->createGroupFromSelection();

            int groupId = ids[TEST_OBJECTS_COUNT - 1] + 1;
            ids[TEST_OBJECTS_COUNT] = groupId;
            objs[TEST_OBJECTS_COUNT] = m_tstModel->getObjectById(groupId);
            visObj[TEST_OBJECTS_COUNT] = m_tstScene->getObjectById(groupId);

            QVERIFY(visObj[TEST_OBJECTS_COUNT] != NULL);
            //So group object created

            m_tstScene->clearSelection();
            visObj[TEST_OBJECTS_COUNT]->setSelected(true);
            m_tstView->removeSelectedObjects();

            for (int i = 0; i < TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT; i++)
            {
                objs[i] = m_tstModel->getObjectById(ids[i]);
                visObj[i] = m_tstScene->getObjectById(ids[i]);
            }

            // Check which object were removed
            // 1 - !NULL, 0 - NULL
            bool states[] = { 0, 0, 1, 1, 1, 0 };
            for (int i = 0; i < TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT - 1; i++)
            {
                QCOMPARE(objs[i] != NULL, states[i]);
                QCOMPARE(visObj[i] != NULL, states[i]);
            }

            //Create new group to test ungrouping
            visObj[2]->setSelected(true);
            visObj[3]->setSelected(true);
            m_tstView->createGroupFromSelection();
            groupId++;
            ids[TEST_OBJECTS_COUNT] = groupId;
            objs[TEST_OBJECTS_COUNT] = m_tstModel->getObjectById(groupId);
            visObj[TEST_OBJECTS_COUNT] = m_tstScene->getObjectById(groupId);

            QVERIFY(visObj[TEST_OBJECTS_COUNT] != NULL);
            // So group object created

            m_tstScene->clearSelection();
            visObj[TEST_OBJECTS_COUNT]->setSelected(true);
            m_tstView->ungroupSelectedObjects();

            for (int i = 0; i < TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT; i++)
            {
                objs[i] = m_tstModel->getObjectById(ids[i]);
                visObj[i] = m_tstScene->getObjectById(ids[i]);
            }

            // States should be the same, cuz we just grouped-ungrouped objects
            for (int i = 0; i < TEST_OBJECTS_COUNT + GROUP_OBJECTS_COUNT - 1; i++)
            {
                QCOMPARE(objs[i] != NULL, states[i]);
                QCOMPARE(visObj[i] != NULL, states[i]);
            }
            clear();
        }
    }; // class GraphView_Test

} // end of namespace Test
