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

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    ObjectVisualType getType() const;
    void setType(const ObjectVisualType &type);
    GraphScene *scene() const;

    void addLink(quint32 linkId);

    QList<quint32> getLinks() const;
    void setLinks(const QList<quint32> &links);

protected:
    QList<quint32> m_links;
    ObjectVisualType m_type;
};

#endif // OBJECTVISUAL_H
