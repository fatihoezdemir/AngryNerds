#include "staticobject.h"

staticObject::staticObject(const QPixmap &pixmap, QPointF pos,
                           QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
      origPos(pos)
{
    this->setPos(origPos);
}


QPointF staticObject::getPos() {
    return origPos;
}

void staticObject::setOrigPos(QPointF pos) {
    origPos = pos;
}

/*QPainterPath staticObject::shape() const {
    return QPainterPath();
}*/
