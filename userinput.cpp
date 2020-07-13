#include "userinput.h"
#include <QCursor>
#include <QMouseEvent>
#include <QCoreApplication>

UserInput::UserInput(Projectile* proj, QWidget *parent)
{
    QCoreApplication::instance()->installEventFilter(this);
}


void UserInput::mousePressEvent(QMouseEvent *event) {
    //Position is mapped to QPointF inPoint
    startPoint = QCursor::pos();
}

void UserInput::mouseReleaseEvent(QMouseEvent *event) {
    //Position is mapped to QPointFOutPoint
    //forceTranslation is done and fed to m_projectile->shoot(vector);
    endPoint = QCursor::pos();
    m_projectile->shoot(forceTranslation());
}

b2Vec2 UserInput::forceTranslation(qreal factor) {
    QPointF finVec = startPoint - endPoint;
    return (b2Vec2(static_cast<float>(finVec.x()*factor), static_cast<float>(finVec.y()*factor)));
}

bool UserInput::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        startPoint = QCursor::pos();
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        endPoint = QCursor::pos();

    }
}

