#include "globalvariables.h"
#include <QtMath>

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
    // converts a QPointF to a b2Vec2
    return (b2Vec2(static_cast<float>(point.x()) * mpp, static_cast<float>(point.y()) * mpp * (-1)));
}

float conv::deg2Rad(qreal deg){
    // converts QT degrees to B2D radians; B2D:counterclockwise, QT:Clockwise -> *(-1)
    return (static_cast<float>(deg) * (-1) * 2 * M_PI / 360);
}

qreal conv::rad2deg(float rad){
    // converts Box2D radians to degrees; B2D:counterclockwise, QT:Clockwise -> *(-1)
    return (static_cast<qreal>(rad) * (-180) / M_PI);
}
