#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include "common/IScaObject.h"
#include "node.h"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = 0);

   QGraphicsItem *addNode(IScaObject *object);
signals:

public slots:

};

#endif // GRAPHSCENE_H
