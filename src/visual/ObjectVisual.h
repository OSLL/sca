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
    ObjectVisual(IScaObject *obj, ObjectVisualType type = OBJECT, QGraphicsItem *parent = 0);
    ~ObjectVisual();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    ObjectVisualType getType() const;
    void setType(const ObjectVisualType &type);
    GraphScene *scene() const;

    void addLink(int linkId);
    void disconnectLink(int linkId);

    QList<int> getLinks() const;
    void setLinks(const QList<int> &links);

    void setFiltered(bool filtered);

    friend QDebug operator<<(QDebug d, ObjectVisual &node);
protected:
    QList<int> m_links;
    ObjectVisualType m_type;
    bool m_filtered;
};

#endif // OBJECTVISUAL_H
