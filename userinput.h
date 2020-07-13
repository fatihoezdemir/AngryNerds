#ifndef USERINPUT_H
#define USERINPUT_H

#include <QMouseEvent>
#include <projectile.h>
#include <box2d/box2d.h>
#include <QScrollArea>

class UserInput : QScrollArea
{
public:
    explicit UserInput(Projectile* proj, QWidget *parent = 0);

    b2Vec2 forceTranslation(qreal factor = 1.0);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QPointF startPoint;
    QPointF endPoint;
    b2Vec2 initVec;
    Projectile* m_projectile;
};

#endif // USERINPUT_H

/* QEvent::MouseButtonPress, QEvent::MouseButtonRelease, QEvent::MouseButtonDblClick, or QEvent::MouseMove.*/
