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

    void addLinkFrom(quint32 linkId);
    QList<quint32> getLinksTo() const;
    void setLinksTo(const QList<quint32> &linksTo);

    void addLinkTo(quint32 linkId);
    QList<quint32> getLinksFrom() const;
    void setLinksFrom(const QList<quint32> &linksFrom);
protected:
    QList<quint32> m_linksFrom;
    QList<quint32> m_linksTo;
    ObjectVisualType m_type;
};

#endif // OBJECTVISUAL_H
