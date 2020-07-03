#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QPropertyAnimation>
#include <QVector>
#include "backgrounditem.h"
#include "flieger.h"
#include "goal.h"
#include "staticobject.h"
#include "box2d/box2d.h"
#include "globalvariables.h"
#include "dynamicobject.h"


class Level : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor
               READ jumpFactor
               WRITE setJumpFactor
               NOTIFY jumpFactorChanged)

public:
    explicit Level(QObject* parent = nullptr);

    QGraphicsView* view;

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent *event);

protected slots:
    void movePlayer();
    void checkTimer();
    void checkColliding();

protected:
    // initializes PlayField
    void initPlayField();

    // ViewPort setup to be FHD and start at the left
    void viewportSetup(QRectF sceneRect = QRectF(0,0,1920,1080), int height = 1080, int width=1920);

    int m_fieldWidth;
    int m_worldShift;
    int m_velocity;

    qreal m_minX;
    qreal m_maxX;
    qreal m_currentX;
    qreal m_groundLevel;

    qreal lastX;

    // Player and Target
    Flieger* m_flieger;
    Goal* m_goal;

    QTimer m_timer;

    // Background Items no physics interactions
    QVector<BackgroundItem*> bgItems;

    // Static Objects
    QVector<staticObject*> staticObjects;

    // dynamic Objects
    QVector<DynamicObject*> dynamicObjects;


protected:
    int m_horizontalInput;
    void addHorizontalInput(int input);

    void applyParallax(qreal xPos, BackgroundItem* item);


// Jump Stuff - To be removed with physics engine //
public:
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

signals:
    void jumpFactorChanged(qreal);

protected:
        void jump();

    int m_jumpHeight;
    qreal m_jumpFactor;
    QPropertyAnimation* m_jumpAnimation;
//^ Jump Stuff - To be removed with physics engine ^//

//BOX2D PHYSICS//
protected:
    b2World* world;

};

#endif // LEVEL_H
