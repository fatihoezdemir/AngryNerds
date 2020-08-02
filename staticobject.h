#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>
#include "box2d/box2d.h"

class StaticObject : public QGraphicsPixmapItem
{
    /// Class to hold a static object that keeps its relative position in the scene. Box2D Phyics interaction
public:
    explicit StaticObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), qreal zVal = 0, b2World* world = nullptr,  QGraphicsItem* parent = nullptr);
    explicit StaticObject(const QPixmap &pixmap, b2PolygonShape boundPoly, qreal zVal = 0, QPointF pos = QPointF(0.0,0.0), b2World* world = nullptr,  QGraphicsItem* parent = nullptr);

    virtual QPainterPath shape() const;
    qreal getOffset();

    virtual void createB2D(b2World* world);
protected:
    QPointF origPos;

    b2BodyDef* objectBodyDef;
    b2Body* objectBody;
    b2PolygonShape objectBox;
};

#endif // STATICOBJECT_H
