#ifndef GOAL_H
#define GOAL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSound>

class Goal : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal rect READ scale WRITE setScale)
public:
    explicit Goal(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void explode();

private:
    bool m_explosion;
};

#endif // GOAL_H

