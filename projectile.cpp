#include "projectile.h"
#include "globalvariables.h"

Projectile::Projectile(const QPixmap &pixmap, QPointF pos, b2World* world, QGraphicsItem* parent, bool isEllipse)
    :  DynamicObject(pixmap, pos, world, parent, isEllipse)
{
    objectFixture.density = 1.0f;
    objectBody->SetAwake(false);
}

Projectile::Projectile(const QPixmap &pixmap, b2PolygonShape boundPoly, QPointF pos, b2World* world, QGraphicsItem* parent)
    :  DynamicObject(pixmap, boundPoly, pos, world, parent)
{
    objectFixture.density = 1.0f;
    objectBody->SetAwake(false);
}

void Projectile::shoot(b2Vec2 initVec){
    //objectBodyDef->gravityScale = 1.0;
    objectBody->ApplyLinearImpulseToCenter(initVec, true);
}

QPainterPath Projectile::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
