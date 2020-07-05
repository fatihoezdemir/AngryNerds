#include "flieger.h"


Flieger::Flieger(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent),
      m_direction(0)
{
    QPixmap pixmap(":/imgs/png/flieger.png");
    setPixmap(pixmap);
    setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
}


int Flieger::direction() const {
    return m_direction;
}

void Flieger::setDirection(int direction) {
    m_direction = direction;
    if (m_direction !=0) {
        QTransform transform;
        if (m_direction < 0) {
            transform.scale(-1,1);
        }
        setTransform(transform);
    }
}

