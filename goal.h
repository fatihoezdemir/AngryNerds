#ifndef GOAL_H
#define GOAL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSound>

class Goal : public QObject, public QGraphicsPixmapItem
{
    // Goal Animation
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal rect READ scale WRITE setScale)
public:
    explicit Goal(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    /// Function trigger when goal is hit by projectile
    void explode();

private:
    /// explosion function flag
    bool m_explosion;
};

#endif // GOAL_H

