#include "goal.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPen>

Goal::Goal(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent),
    m_explosion(false)
{
    // Center the Goals Coordinates
    setOffset(-pixmap.width()/2,-pixmap.height()/2);
}

void Goal::explode() {
    if (m_explosion) {
        // Goal was already hit
        return;
    }
    // Set the explosion flag on first hit by projectile
    m_explosion = true;

    // Set Up Goal Animation
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    QPropertyAnimation *scaleAnimation = new QPropertyAnimation(this, "rect");
    scaleAnimation->setDuration(700);

    qreal scl = scale();
    scaleAnimation->setStartValue(scl);
    scaleAnimation->setEndValue(0.0);
    scaleAnimation->setEasingCurve(QEasingCurve::OutQuart);
    group->addAnimation(scaleAnimation);

    QPropertyAnimation *fadeAnimation = new QPropertyAnimation(this, "opacity");
    fadeAnimation->setDuration(700);
    fadeAnimation->setStartValue(1);
    fadeAnimation->setEndValue(0);
    fadeAnimation->setEasingCurve(QEasingCurve::OutQuart);
    group->addAnimation(fadeAnimation);

    connect(group, &QParallelAnimationGroup::finished,
            this, &Goal::deleteLater);
    group->start();
}
