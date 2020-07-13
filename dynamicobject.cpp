#include "dynamicobject.h"
#include "globalvariables.h"
#include <QDebug>
DynamicObject::DynamicObject(const QPixmap &pixmap, QPointF pos,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);

    // Create the object also in box2D
    objectBodyDef = new b2BodyDef();
    objectBodyDef->type = b2_dynamicBody;
    b2Vec2 b2Pos = conv::p2mVec(pos);
    objectBodyDef->position.Set(conv::p2m(pos.x()), conv::p2m(pos.y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox;
    objectBox.SetAsBox(conv::p2m(this->boundingRect().width()/2), conv::p2m(this->boundingRect().height()/2),
                       b2Vec2(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2), 0);

    objectFixture.shape = &objectBox;
    objectFixture.restitution = 0.6;
    objectFixture.density = 1.0f;
    objectFixture.friction = 0.3f;

    objectBody->CreateFixture(&objectFixture);
}

DynamicObject::DynamicObject(const QPixmap &pixmap, b2PolygonShape boundPoly, QPointF pos,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);

    // Create the object also in box2D
    objectBodyDef = new b2BodyDef();
    objectBodyDef->type = b2_dynamicBody;
    b2Vec2 b2Pos = conv::p2mVec(pos);
    objectBodyDef->position.Set(conv::p2m(pos.x()), conv::p2m(pos.y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox = boundPoly;
    objectFixture.shape = &objectBox;
    objectFixture.restitution = 0.6;
    objectFixture.density = 1.0f;
    objectFixture.friction = 0.3f;

    objectBody->CreateFixture(&objectFixture);
}


QPointF DynamicObject::getPos() {
    return conv::m2pVec(objectBody->GetPosition());
}

qreal DynamicObject::getRot() {
    return conv::rad2deg(objectBody->GetAngle());
}

void DynamicObject::updatePos(QPointF pos) {
    this->setPos(pos.x(), pos.y());
}

void DynamicObject::updateRot(qreal rot) {
    this->setRotation(rot);
}

QPainterPath DynamicObject::shape() const {
    return QPainterPath();
}
