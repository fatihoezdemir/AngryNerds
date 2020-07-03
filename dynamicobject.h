#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>
#include "box2d/box2d.h"

class DynamicObject : public QGraphicsPixmapItem
{
public:
    explicit DynamicObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr);

    QPointF getPos();
    qreal getOffset();
    qreal getRot();

    virtual QPainterPath shape() const; // might be removed

    void updatePos(QPointF pos);

    void updateRot(qreal rot);

protected:
    QPointF origPos;

    b2BodyDef* objectBodyDef;
    b2Body* objectBody;
    b2PolygonShape objectBox;
    b2FixtureDef objectFixture;
};

#endif // DYNAMICOBJECT_H
