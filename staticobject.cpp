#include "staticobject.h"
#include "globalvariables.h"
StaticObject::StaticObject(const QPixmap &pixmap, QPointF pos, qreal zVal,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);
    setZValue(zVal);
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

StaticObject::StaticObject(const QPixmap &pixmap, b2PolygonShape boundPoly, qreal zVal, QPointF pos,
                           b2World* world, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    setPos(pos);
    setZValue(zVal);
    objectBodyDef = new b2BodyDef();
    objectBodyDef->position.Set(conv::p2m(pos.x()), conv::p2m(pos.y(), true));
    objectBody = world->CreateBody(objectBodyDef);
    b2PolygonShape objectBox = boundPoly;
    /*objectBox.SetAsBox(conv::p2m(boundingRect().width())/2, conv::p2m(boundingRect().height())/2,
                       b2Vec2(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2), 0);*/
    objectBody->CreateFixture(&objectBox, 0.0);
}


QPointF StaticObject::getPos() {
    return origPos;
}

QPainterPath StaticObject::shape() const {
    return QPainterPath();
}


