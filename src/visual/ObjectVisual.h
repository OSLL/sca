#ifndef OBJECTVISUAL_H
#define OBJECTVISUAL_H

#include <QAbstractGraphicsShapeItem>
#include "../common/IScaObject.h"
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
    virtual void setStandardColor(const QColor &color) = 0;
    virtual QColor getStandardColor() const = 0;
    GraphScene *scene() const;

    void setX(qreal x);
    void setY(qreal y);

    void addLink(int linkId);
    void disconnectLink(int linkId);

    void refreshToolTip(IScaObject *obj);

    void deleteAnnotation();
    void setAnnotation(QGraphicsTextItem *annotation);
    void setAnnotation(const QString &str);
    QString getAnnotationText() const;
    QGraphicsTextItem *getAnnotation() const;

    QList<int> getLinks() const;
    void setLinks(const QList<int> &links);

    virtual void setFiltered(bool filtered) = 0;

    friend QDebug operator<<(QDebug d, ObjectVisual &node);
protected:
    QList<int> m_links;
    ObjectVisualType m_type;
    bool m_filtered;
    QGraphicsTextItem *m_annotation;
};

#endif // OBJECTVISUAL_H
