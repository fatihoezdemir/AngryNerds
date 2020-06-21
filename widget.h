#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <box2d/box2d.h>
#include <QVector>
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
Q_OBJECT

public:
explicit Widget(QWidget *parent = 0);
~Widget();

protected:
void timerEvent(QTimerEvent *event);
void mousePressEvent(QMouseEvent *event);

private:
void createWall();
void createBall();

private:
Ui::Widget *ui;
QGraphicsScene* scene;
QGraphicsView* view;
b2World* world;
QVector<b2Body*> balls;
};

#endif // WIDGET_H
