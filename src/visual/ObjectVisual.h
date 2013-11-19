#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include <QAbstractGraphicsShapeItem>
#include "common/IScaObject.h"
class GraphScene;

class ObjectVisual : public QAbstractGraphicsShapeItem
{
public:
    enum ObjectVisualType{
        OBJECT,
        NODE,
        LINK,
        COMMENT
    };
    ObjectVisual(ObjectVisualType type = OBJECT, QGraphicsItem *parent = 0);
    ~ObjectVisual();

    ObjectVisualType getType() const;
    void setType(const ObjectVisualType &type);
    GraphScene *scene() const;
protected:
    ObjectVisualType m_type;
};

#endif // OBJECTVISUAL_H
