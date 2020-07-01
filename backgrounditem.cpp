#include "backgrounditem.h"

#include <QPainterPath>

BackgroundItem::BackgroundItem(const QPixmap &pixmap, QPointF pos,
                               qreal offset, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent),
    origPos(pos),
    parOffset(offset)
{
    this->setPos(origPos);
}


QPainterPath BackgroundItem::shape() const {
    return QPainterPath();
}

QPointF BackgroundItem::getPos() {
    return origPos;
}

qreal BackgroundItem::getOffset(){
    return parOffset;
}
