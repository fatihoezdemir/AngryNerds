#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "dynamicobject.h"

class Projectile : public DynamicObject
{
public:
    explicit Projectile(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr);
    void shoot(b2Vec2 initVec = b2Vec2(5.0,2.0));

    virtual QPainterPath shape() const; // might be removed

};

#endif // PROJECTILE_H

