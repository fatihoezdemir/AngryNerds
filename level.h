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

// Jump Stuff - To be removed with physics engine //
public:
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

signals:
    void jumpFactorChanged(qreal);

private:
    void jump();

    int m_jumpHeight;
    qreal m_jumpFactor;
    QPropertyAnimation* m_jumpAnimation;
//^ Jump Stuff - To be removed with physics engine ^//

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent *event);

private slots:
    void movePlayer();
    void checkTimer();
    void checkColliding();

private:
    void initPlayField();



    int m_fieldWidth;
    int m_worldShift;
    int m_velocity;

    qreal m_minX;
    qreal m_maxX;
    qreal m_currentX;
    qreal m_groundLevel;

    qreal lastX;

    // Projectile
    Flieger* m_flieger;
    Goal* m_goal;
    QTimer m_timer;

    BackgroundItem* m_wall; // should be in every level
    BackgroundItem* m_sky; // should be in every level
    BackgroundItem* m_lamp; // could be put into Vector
    BackgroundItem* m_table; // could be put into Vector
    QVector<BackgroundItem*> bgItems;

private:

    int m_horizontalInput;
    void addHorizontalInput(int input);
    //void applyParallax(qreal ratio, QGraphicsItem* item);
    void applyParallax(qreal xPos, BackgroundItem* item);

// Update Viewport based on position
//public:
//    void changeViewport(qreal dx);
};

#endif // LEVEL_H
