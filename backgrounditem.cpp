#include "backgrounditem.h"

#include <QPainterPath>

BackgroundItem::BackgroundItem(const QPixmap &pixmap, QPointF pos,
                               qreal offset, qreal zVal, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
    origPos(pos),
    parOffset(offset)
{
    // set its initial position
    this->setPos(origPos);
    // set zValue to ensure proper visibility
    this->setZValue(zVal);
}


QPainterPath BackgroundItem::shape() const {
    // empty path, so no interaction is done with the projectile or other objects
    return QPainterPath();
}

QPointF BackgroundItem::getPos() {
    // used for grpahics update
    return origPos;
}

qreal BackgroundItem::getOffset(){
    // used for grpahics update
    return parOffset;
}
