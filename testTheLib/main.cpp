#include <box2d/box2d.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    b2Vec2 gravity(0.00f, 10.00f);
    b2World* world = new b2World(gravity);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Body* body = world->CreateBody(&bodyDef);
    b2CircleShape shape;
    shape.m_radius = 1.00f;

    body->CreateFixture(&shape, 1.00f);

    for (int i = 0; i<100; i++){
        world->Step(1.0f/50.00f, 6, 2);
        qDebug() << body->GetPosition().y;
    }
}
