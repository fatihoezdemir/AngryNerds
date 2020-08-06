#include "forcefield.h"
#include "globalvariables.h"

ForceField::ForceField(const QPixmap &pixmap, QPointF pos, qreal zVal,b2Vec2 force, QGraphicsItem* parent) :
    BackgroundItem(pixmap, pos, 0.0, zVal, parent),
    initVec(force)
{
}

b2Vec2 ForceField::getField(){
    return initVec;
}

QPainterPath ForceField::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
