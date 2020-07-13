#ifndef MENSA_H
#define MENSA_H
#include "level.h"

class Mensa : public Level
{
public:
    Mensa(QObject* parent = nullptr, QPointF initDim = QPointF(10000,2000));
    virtual void initPlayField() override;
};

#endif // MENSA_H
