#include "staticobject.h"
#include "globalvariables.h"
staticObject::staticObject(const QPixmap &pixmap, QPointF pos,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);

    // Create the object also in box2D
    objectBodyDef = new b2BodyDef();
    //b2Vec2 b2Pos = conv::p2mVec(pos);
    objectBodyDef->position.Set(conv::p2m(pos.x()), conv::p2m(pos.y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox;
    objectBox.SetAsBox(conv::p2m(boundingRect().width())/2, conv::p2m(boundingRect().height())/2,
                       b2Vec2(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2), 0);
    objectBody->CreateFixture(&objectBox, 0.0);
}

QPointF staticObject::getPos() {
    return origPos;
}

void staticObject::setOrigPos(QPointF pos) {
    origPos = pos;
}

QPainterPath staticObject::shape() const {
    return QPainterPath();
}
