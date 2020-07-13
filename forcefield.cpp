#include "forcefield.h"
#include "globalvariables.h"

ForceField::ForceField(const QPixmap &pixmap, QPointF pos,
                       qreal offset, qreal zVal ,b2Vec2 force,QGraphicsItem* parent
                         ) :
    BackgroundItem(pixmap, pos, offset, zVal, parent),
    initVec(force)
{

}

/*void ForceField::shoots(b2Vec2 initVec)
{
    //objectBodyDef->gravityScale = 1.0;
 //   projectile->shoot(initVec);
    //ob//jectBody->ApplyLinearImpulseToCenter(initVec, true);
}*/

b2Vec2 ForceField::getField(){
    return initVec;
}

QPainterPath ForceField::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
