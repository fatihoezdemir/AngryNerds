#ifndef CVL_H
#define CVL_H
#include "level.h"

class Cvl : public Level
{
public:
    Cvl(QObject* parent = nullptr, QPointF initDim = QPointF(5000, 2500));

    virtual void initPlayField() override;
};

#endif // CVL_H
