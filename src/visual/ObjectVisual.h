#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include "common/IScaObject.h"
#include <QAbstractGraphicsShapeItem>


class ObjectVisual : public QAbstractGraphicsShapeItem
{
public:
    enum ObjectVisualType{
        OBJECT,
        NODE,
        EDGE,
        COMMENT
    };
    ObjectVisual(IScaObject *object, ObjectVisualType type = OBJECT, QGraphicsItem *parent = 0);

    IScaObject *getObject() const;
    void setObject(IScaObject *object);

protected:
    ObjectVisualType m_type;
    IScaObject *m_object;
};

#endif // OBJECTVISUAL_H
