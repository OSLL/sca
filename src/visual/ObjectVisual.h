#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include <QAbstractGraphicsShapeItem>
#include "common/IScaObject.h"

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
    ~ObjectVisual();

    IScaObject *getObject() const;
    void setObject(IScaObject *object);

    IScaObject::IScaObjectType getObjectType() const;

    ObjectVisualType getType() const;
    void setType(const ObjectVisualType &type);
protected:
    ObjectVisualType m_type;
    IScaObject *m_object;
};

#endif // OBJECTVISUAL_H
