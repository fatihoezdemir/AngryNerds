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
#include "projectile.h"
#include "forcefield.h"
class Level : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor
               READ jumpFactor
               WRITE setJumpFactor
               NOTIFY jumpFactorChanged)

public:
    explicit Level(QObject* parent = nullptr, QPointF initDim = QPointF(3840.0, 1080.0));

    QGraphicsView* view;

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent *event);

    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

protected slots:
    void movePlayer();
    void checkTimer();
    void checkColliding();

public:
    // initializes PlayField
    virtual void initPlayField();
protected:
    // ViewPort setup to be FHD and start at the left
    void viewportSetup(QRectF sceneRect = QRectF(0,0,1920,1080), int height = conv::viewHeight, int width=conv::viewWidth);

    QPointF sceneDim;

    qreal m_currentX;
    qreal m_groundLevel;

    qreal lastX;

    // Player and Target
    Flieger* m_flieger;
    Goal* m_goal;
    Projectile* m_projectile;

    QTimer m_timer;
    //UserInput* m_input;

    // Background Items no physics interactions
    QVector<BackgroundItem*> bgItems;
    // Static Objects
    QVector<StaticObject*> staticObjects;
    // dynamic Objects
    QVector<DynamicObject*> dynamicObjects;
    // Force Field
    QVector <ForceField*> forceFields;

protected:
    void applyParallax(qreal xPos, BackgroundItem* item);
    void updateView();


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
