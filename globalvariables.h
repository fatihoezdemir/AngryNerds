#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <QPointF>
#include "box2d/box2d.h"

namespace conv {
    inline qreal const sceneWidth = 3840;   // px
    inline qreal const sceneHeight = 1080;  // px
    inline qreal const viewWidth = 1920;    // px
    inline qreal const viewHeight = 1080;   // px

    // Global Box 2D height of the level
    inline float const b2Height = 5;  // meters

    inline qreal const xBoundary = 1000.0;
    inline qreal const yBoundary = 600.0;

    // Conversion Factors used to calculated between B2D and QT
    inline float const ppm = sceneHeight/b2Height;  // px/m
    inline float const mpp = b2Height/sceneHeight;  //  m/px
}

// [CONVERSION FUNCTIONS] //
namespace conv {
    qreal m2p(float mets, bool isY = false); // converts a single value from meters to px !!Box2D flips y coordinate, set isY=true for right calc!!
    float p2m(qreal px, bool isY = false); //  converts a single value from px to meters !!Box2D flips y coordinate, set isY=true for right calc
    QPointF m2pVec(b2Vec2 vec); // converts a b2Vec2 point in px to a QPointF in px
    b2Vec2 p2mVec(QPointF point); // converts QPointD in px to B2Vec2 in m
    float deg2Rad(qreal deg); // Qt degrees to Box2D radians
    qreal rad2deg(float rad); // Box2D radians to Qt degrees
}

#endif // GLOBALVARIABLES_H
