#include "staticobject.h"
#include "globalvariables.h"
StaticObject::StaticObject(const QPixmap &pixmap, QPointF pos,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);
    createB2D(world);
}

void StaticObject::createB2D(b2World* world){
    // Create the object also in box2D
    objectBodyDef = new b2BodyDef();
    objectBodyDef->position.Set(conv::p2m(pos().x()), conv::p2m(pos().y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox;
    objectBox.SetAsBox(conv::p2m(boundingRect().width())/2, conv::p2m(boundingRect().height())/2,
                       b2Vec2(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2), 0);
    objectBody->CreateFixture(&objectBox, 0.0);
}

QPointF StaticObject::getPos() {
    return origPos;
}

/*void StaticObject::setOrigPos(QPointF pos) {
    origPos = pos;
}*/

QPainterPath StaticObject::shape() const {
    return QPainterPath();
}


