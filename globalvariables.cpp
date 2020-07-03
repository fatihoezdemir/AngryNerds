#include "globalvariables.h"

qreal conv::m2p(float mets, bool isY){
    //  converts a single value from m to px !!Box2D flips y coordinate, so don't use for y use m2pVec instead!!
    float coeff = 1;
    if(isY) coeff = -1;
    return static_cast<qreal>(mets*ppm*coeff);
}

float conv::p2m(qreal point, bool isY){
    //  converts a single value from px to meters !!Box2D flips y coordinate, so don't use for y use p2mVec instead!!
    float coeff = 1;
    if(isY) coeff = -1;
    return (static_cast<float>(point))*mpp*coeff;
}

QPointF conv::m2pVec(b2Vec2 vec){
    // converts a b2Vec2 point in px to a QPointF in px
    return (QPointF(static_cast<qreal>(vec.x*ppm), static_cast<qreal>(vec.y*ppm*(-1))));
}

b2Vec2 conv::p2mVec(QPointF point){
    return (b2Vec2(static_cast<float>(point.x()) * mpp, static_cast<float>(point.y()) * mpp * (-1)));
}
