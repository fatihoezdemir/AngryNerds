#include "projectile.h"
#include "globalvariables.h"
#include <QtMath>
#include <QTimer>
#include <iostream>

Projectile::Projectile(const QPixmap &pixmap, projectile proj,QPointF pos, b2World* world, QGraphicsItem* parent)
    :  DynamicObject(pixmap, pos, world, parent), shot(false), running(false)
{
    objectBody->DestroyFixture(&objectBody->GetFixtureList()[0]); //

    if(proj == Projectile::PLANE) {
        b2Vec2 vertices[3];
        vertices[0].Set(conv::p2m(0), conv::p2m(0, true));
        vertices[1].Set(conv::p2m(200), conv::p2m(100, true));
        vertices[2].Set(conv::p2m(0), conv::p2m(100, true));
        vertices[3].Set(conv::p2m(20), conv::p2m(30, true));
        b2PolygonShape polygon;
        polygon.Set(vertices, 4);
        objectFixture.shape = &polygon;
        objectFixture.density = 2.0;
        objectFixture.friction = 0.2;
        objectFixture.restitution = 0.5;
        objectBody->CreateFixture(&objectFixture);
        objectBody->SetAngularDamping(5.0);
    } else if (proj == Projectile::TOMATO) {
        b2CircleShape objectBox;
        objectBox.m_radius = conv::p2m(this->boundingRect().width()/2);
        objectBox.m_p.Set(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2);
        objectFixture.shape = &objectBox;
        objectFixture.restitution = 0.2;
        objectFixture.density = 0.8;
        objectFixture.friction = 0.3;

        objectBody->CreateFixture(&objectFixture);
    } else if ( proj == Projectile::BALL) {
        // HAS TO BE CHANGED ... PROBABLY
        b2CircleShape objectBox;
        objectBox.m_radius = conv::p2m(this->boundingRect().width()/2);
        objectBox.m_p.Set(conv::p2m(boundingRect().width())/2, conv::p2m(-boundingRect().height())/2);
        objectFixture.shape = &objectBox;
        objectFixture.restitution = 0.1;
        objectFixture.density = 3;
        objectFixture.friction = 0.3;
        objectBody->CreateFixture(&objectFixture);
    }
    objectBody->SetAwake(false);
    outTimer = new QTimer();
}


void Projectile::shoot(b2Vec2 initVec){
    objectBody->ApplyLinearImpulseToCenter(initVec, true);
    recentSpeed = objectBody->GetLinearVelocity().Length();
    shot = true;
}

void Projectile::checkVelocity(){
    // checks if objects is not moving anymore
    float speedNow = objectBody->GetLinearVelocity().Length();
    recentSpeed = 0.1 * speedNow + 0.9 * recentSpeed;
    // start Timer if projectile was shot and is not moving anymore
    if ((recentSpeed <= 1.0 ) && !running && shot) {
        outTimer->start(1000); // starts timer with 1s timeout
        running = true;
        std::cout << "Timer started" << std::endl;
    } else if ((recentSpeed > 0.1) && running && shot) {
        // timer gets deleted if object is moving again
        outTimer->stop();
        running = false;
        std::cout << "Timer stopped" << std::endl;
    }
}

QPainterPath Projectile::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
