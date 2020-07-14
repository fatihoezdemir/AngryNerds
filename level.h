#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QPropertyAnimation>
#include <QVector>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include "backgrounditem.h"
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

public:
    explicit Level(QObject* parent = nullptr, QPointF initDim = QPointF(3840.0, 1080.0));

    QGraphicsView* view;

protected:
    void timerEvent(QTimerEvent *event);
    void checkFinish();

    void checkFinish();
protected slots:
    void checkColliding();
    void on_ProjectileTimeout();

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
    Projectile* m_projectile;
    Goal* m_goal;

    QTimer m_timer;
    //UserInput* m_input;

    // Background Items no physics interactions
    QVector<BackgroundItem*> bgItems;
    // Static Objects
    QVector<StaticObject*> staticObjects;
    // dynamic Objects
    QVector<DynamicObject*> dynamicObjects;
    QVector<DynamicObject*> movingObjects;
    // Force Field Objects
    QVector<ForceField*> forceFields;

    //arrow
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    QGraphicsLineItem *arrowLine;
    QGraphicsEllipseItem *arrowDot;
    qreal arrowInitX;
    qreal arrowInitY;
    qreal arrowFinalX;
    qreal arrowFinalY;
    qreal shootingAngle;
    bool arrowDragged;
    bool mouseReleased;

    //adjust view position manually
    void keyPressEvent(QKeyEvent *event);
    qreal viewOffset;

    //initial position of projectile
    QPointF initProj;

protected:
    void applyParallax(qreal xPos, BackgroundItem* item);
    void updateView();

//BOX2D PHYSICS//
protected:
    b2World* world;

};

#endif // LEVEL_H
