#ifndef BIB_H
#define BIB_H

#include <QGraphicsScene>
#include <QWidget>
#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include "backgrounditem.h"
#include "flieger.h"
#include "level.h"
#include <QPropertyAnimation>

class Bib : public Level
{
    Q_OBJECT
    /*Q_PROPERTY(qreal jumpFactor
               READ jumpFactor
               WRITE setJumpFactor
               NOTIFY jumpFactorChanged)*/

public:
    explicit Bib(QObject* parent = nullptr);
/*
    qreal jumpFactor() const;
    int m_worldShift;
    int m_velocity;

    qreal m_minX;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void movePlayer();
    void checkTimer();
    //  void checkColliding();

signals:
    void jumpFactorChanged(qreal);

private:
    void initPlayField();
    void jump();

    int m_fieldWidth;
    int m_worldShift;
    int m_velocity;
    int m_jumpHeight;
    qreal m_minX;
    qreal m_maxX;
    qreal m_currentX;
    qreal m_groundLevel;
    qreal m_jumpFactor;

    QPropertyAnimation* m_jumpAnimation;

    Flieger* m_flieger;

    QGraphicsView* view;
    QTimer m_timer;

    BackgroundItem* m_wall;
    BackgroundItem* m_lamp;
    BackgroundItem* m_sky;
    BackgroundItem* m_table;

    int m_horizontalInput;
    void addHorizontalInput(int input);
    void applyParallax(qreal ratio, QGraphicsItem* item);
*/
};

#endif // BIB_H
