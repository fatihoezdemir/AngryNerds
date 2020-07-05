#ifndef FLIEGER_H
#define FLIEGER_H

#include <QGraphicsPixmapItem>

class Flieger : public QGraphicsPixmapItem
{
public:
    explicit Flieger(QGraphicsItem* parent = 0);
    void setDirection(int direction);
    int direction() const;

private:
    int m_direction;

// signals:
//    void positionChanged(qreal dx);
};

#endif // FLIEGER_H
