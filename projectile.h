#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "dynamicobject.h"

class Projectile : public DynamicObject
{
public:
    enum projectile{PLANE, TOMATO, BALL};
    /// [Constructor based on each Projectile]
    explicit Projectile(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr, bool isEllipse = false);
    explicit Projectile(const QPixmap &pixmap, b2PolygonShape boundPoly, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr);
    explicit Projectile(const QPixmap &pixmap, projectile proj, QPointF pos, b2World* world, QGraphicsItem* parent = nullptr);
    void shoot(b2Vec2 initVec = b2Vec2(5.0,2.0));

    virtual QPainterPath shape() const; // might be removed

    void checkVelocity();

    QTimer* outTimer; //Timer signal has to be connected to level reinitialize
    // connect(timer,SIGNAL(timeout()), this,SLOT(on_TimerTick()));

    void changeB2DRot(qreal angle); //adjusts angle of projectile at the time of mouseRelease

    private:

    bool shot;
    bool running;
    float recentSpeed;

signals:
    void levelOver(int won);
};

#endif // PROJECTILE_H
