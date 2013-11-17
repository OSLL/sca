#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

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
    ObjectVisual(ObjectVisualType type = OBJECT, QGraphicsItem *parent = 0);
    ~ObjectVisual();

    ObjectVisualType getType() const;
    void setType(const ObjectVisualType &type);
protected:
    ObjectVisualType m_type;
};

#endif // OBJECTVISUAL_H
