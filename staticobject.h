#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>
#include "box2d/box2d.h"

class staticObject : public QGraphicsPixmapItem
{
public:
    explicit staticObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), b2World* world = nullptr,  QGraphicsItem* parent = nullptr);

    QPointF getPos();
    qreal getOffset();

    virtual QPainterPath shape() const; // will be removed

    void setOrigPos(QPointF pos);
private:
    QPointF origPos;

    b2BodyDef* objectBodyDef;
    b2Body* objectBody;
    b2PolygonShape objectBox;

};

#endif // STATICOBJECT_H
