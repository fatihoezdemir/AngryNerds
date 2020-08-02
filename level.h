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

    /// DataType to hold level
    enum levelNum{ONE, TWO, THREE};


protected:
    /// function that gets called at each level-timer step
    void timerEvent(QTimerEvent *event);
    /// Function to check if projectile is still moving
    void checkFinish();

protected slots:
    /// Check for collisions with Goal or Forcefield
    void checkColliding();
    /// Reaction if projectile is not moving anymore
    void on_ProjectileTimeout();
    /// close level, when game is over
    void levelOver();

public:
    // initializes PlayField
    virtual void initPlayField();

signals:
    /// Player looses the game -> restart the level
    void playerDeath();
    /// Player wins the Game -> load next Level
    void playerWin();

protected:
    // ViewPort setup to be FHD and start at the left
    void viewportSetup(QRectF sceneRect = QRectF(0,0,1920,1080), int height = conv::viewHeight, int width=conv::viewWidth);

    QPointF sceneDim; // Scene Dimensions
    levelNum m_level;

    // [Positioning Information]
    qreal m_currentX;
    qreal m_groundLevel;
    QPointF initProj;
    qreal lastX;

    // Player and Target
    Projectile* m_projectile;
    Goal* m_goal;

    // Timer for updating physics
    QTimer m_timer;
    QTimer* win_timer;

    // [Scene Objects]
    QVector<BackgroundItem*> bgItems;
    QVector<StaticObject*> staticObjects;
    QVector<DynamicObject*> dynamicObjects;
    QVector<DynamicObject*> movingObjects;
    QVector<ForceField*> forceFields;


    // Arrow [ Nico ]
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

    // adjust view position manually
    void keyPressEvent(QKeyEvent *event);
    qreal viewOffset;

protected:
    void applyParallax(qreal xPos, BackgroundItem* item);
    void updateView();

    // [BOX2D PHYSICS]
protected:
    b2World* world;

};

#endif // LEVEL_H
