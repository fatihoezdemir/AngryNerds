#include "projectile.h"
#include "globalvariables.h"
//#include "box2d/box2d.h"

Projectile::Projectile(const QPixmap &pixmap, QPointF pos, b2World* world, QGraphicsItem* parent)
    :  DynamicObject(pixmap, pos, world, parent)
{
    /*
    setPos(pos);
    // Create the object also in box2D
    objectBodyDef = new b2BodyDef();
    objectBodyDef->type = b2_dynamicBody;
    objectBodyDef->gravityScale = 0.0f; // ensures that object stays in place
    b2Vec2 b2Pos = conv::p2mVec(pos);
    objectBodyDef->position.Set(conv::p2m(pos.x()), conv::p2m(pos.y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox;
    objectBox.SetAsBox(conv::p2m(this->boundingRect().width()/2), conv::p2m(this->boundingRect().height()/2),
                        b2Vec2(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2), 0);
    objectFixture.shape = &objectBox;
    objectFixture.restitution = 0.6;
    objectFixture.friction = 0.3f;
    objectBody->CreateFixture(&objectFixture);*/
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
