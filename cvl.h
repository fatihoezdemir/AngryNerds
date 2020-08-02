#ifndef CVL_H
#define CVL_H
#include "level.h"

class Cvl : public Level
{
public:
    Cvl(levelNum lev = ONE, QObject* parent = nullptr, QPointF initDim = QPointF(5000, 2500));

    /// [Main Object initializer]
    virtual void initPlayField() override;

    /// [Level Initializers]
    void initLevel1();
    void initLevel2();
    //void initLevel3();
};

#endif // CVL_H
