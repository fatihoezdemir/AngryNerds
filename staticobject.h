#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>
#include "box2d/box2d.h"
/*
 * This class holds all parameters and functions of a static object that uses Box2D for physics interaction.
*/

class StaticObject : public QGraphicsPixmapItem
{
public:
    explicit StaticObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), qreal zVal = 0, b2World* world = nullptr,  QGraphicsItem* parent = nullptr);
    explicit StaticObject(const QPixmap &pixmap, b2PolygonShape boundPoly, qreal zVal = 0, QPointF pos = QPointF(0.0,0.0), b2World* world = nullptr,  QGraphicsItem* parent = nullptr);

    virtual QPainterPath shape() const;
    qreal getOffset();

    // create a body in the box2d physics simulation based on the pixmap parameters
    virtual void createB2D(b2World* world);
protected:
    QPointF origPos;

    // [Box2D Parameters]
    b2BodyDef* objectBodyDef;
    b2Body* objectBody;
    b2PolygonShape objectBox;
};

#endif // STATICOBJECT_H
