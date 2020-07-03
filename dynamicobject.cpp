#include "dynamicobject.h"
#include "globalvariables.h"

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
    objectBox.SetAsBox(conv::p2m(boundingRect().width()/2), conv::p2m(boundingRect().height()/2));
    objectFixture.shape = &objectBox;
    objectFixture.restitution = 0.9;
    objectFixture.density = 1.0f;
    objectFixture.friction = 0.3f;

    objectBody->CreateFixture(&objectFixture);
}

QPointF DynamicObject::getPos() {
    return conv::m2pVec(objectBody->GetPosition());
}

void DynamicObject::updatePos(QPointF pos) {
    this->setPos(pos.x(), pos.y()); // Make Conversion
}

QPainterPath DynamicObject::shape() const {
    return QPainterPath();
}
