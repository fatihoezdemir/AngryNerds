#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>
#include "box2d/box2d.h"
#include "staticobject.h"

class DynamicObject : public QGraphicsPixmapItem
{
    /*
    Dynamic Object class
    dynamic Objects interact with static objects and each other using Box2D physics and change their positions
    */
public:
    // [Constructors]
    /// Constructor for square or ellipse bounding box
    explicit DynamicObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr, bool isEllipse = false);
    /// Constructor for polygon bounding box
    explicit DynamicObject(const QPixmap &pixmap, b2PolygonShape boundPoly, QPointF pos = QPointF(0.0,0.0), b2World* world = 0, QGraphicsItem* parent = nullptr);

    /// read position, offset and Rotation information
    QPointF getPos();
    qreal getOffset();
    qreal getRot();

    /// Ensures that no collision detection is done using box2D
    virtual QPainterPath shape() const;

    // Physics Simulation
    void updatePos(QPointF pos);
    void updateRot(qreal rot);

    // Oscillation functions
    void oscPos();
    void setOscillation(QPointF amp, qreal freq);

protected:
    // original Position
    QPointF origPos;

    // Box2D Parameters and Bodies
    b2BodyDef* objectBodyDef;
    b2Body* objectBody;
    b2PolygonShape objectBox;
    b2FixtureDef objectFixture;

    // Oscillation Parameters
    QPointF amplitude;
    qreal frequency;
    qreal timestep;
    bool moving;
};

#endif // DYNAMICOBJECT_H
