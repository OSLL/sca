#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include "common/IScaObject.h"
#include <QGraphicsItem>


class ObjectVisual : public QGraphicsItem
{
public:
    ObjectVisual(IScaObject *object, QGraphicsItem *parent=0);

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
private:
    IScaObject *m_object;

};

#endif // OBJECTVISUAL_H
