#ifndef FORCEFIELD_H
#define FORCEFIELD_H
#include "box2d/box2d.h"
//#include "staticobject.h"
#include "dynamicobject.h"
#include "projectile.h"
#include "backgrounditem.h"

class ForceField:public BackgroundItem{
public:
    explicit ForceField(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0),
                        qreal zVal = 0, b2Vec2 force = b2Vec2(-11.1,-111.1),
                        QGraphicsItem* parent = 0);

    QPainterPath shape() const;
    b2Vec2 getField();
private:
    b2Vec2 initVec;
};

#endif // FORCEFIELD_H
