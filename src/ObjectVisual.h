#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include <QGraphicsItem>
#include "common/IScaObject.h"

class ObjectVisual : public QGraphicsItem
{
public:
    ObjectVisual(IScaObject *object = NULL);

    IScaObject *getObject() const;
    void setObject(IScaObject *object);

    enum ObjectVisualType{
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
