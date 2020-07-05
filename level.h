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

class Level : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Level(QObject* parent = nullptr);

    QGraphicsView* view;

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent *event);

    void mousePressEvent(QMouseEvent* event);

protected slots:
    void checkColliding();

protected:
    // initializes PlayField
    void initPlayField();

    // ViewPort setup to be FHD and start at the left
    void viewportSetup(QRectF sceneRect = QRectF(0,0,1920,1080), int height = conv::viewHeight, int width=conv::viewWidth);

    qreal m_currentX;
    qreal m_groundLevel;

    qreal lastX;

    // Player and Target
    Projectile* m_projectile;
    Goal* m_goal;

    QTimer m_timer;

    // Background Items no physics interactions
    QVector<BackgroundItem*> bgItems;

    // Static Objects
    QVector<StaticObject*> staticObjects;

    // dynamic Objects
    QVector<DynamicObject*> dynamicObjects;


protected:
    int m_horizontalInput;
    void addHorizontalInput(int input);

    void applyParallax(qreal xPos, BackgroundItem* item);

//BOX2D PHYSICS//
protected:
    b2World* world;

};

#endif // LEVEL_H
