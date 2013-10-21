#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include "common/IScaObject.h"
#include <QAbstractGraphicsShapeItem>


class ObjectVisual : public QAbstractGraphicsShapeItem
{
public:
    ObjectVisual(IScaObject *object, QGraphicsItem *parent = 0);


    IScaObject *getObject() const;
    void setObject(IScaObject *object);

    enum ObjectVisualType{
        OBJECT,
        NODE,
        EDGE,
        COMMENT
    };

protected:
    ObjectVisualType m_type;
    IScaObject *m_object;
};

#endif // OBJECTVISUAL_H
