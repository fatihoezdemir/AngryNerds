#ifndef MENSA_H
#define MENSA_H
#include "level.h"
#include <QMediaPlayer>

class Mensa : public Level
{
public:
    Mensa(QObject* parent = nullptr, QPointF initDim = QPointF(8000,1500));
    virtual void initPlayField() override;
};

#endif // MENSA_H
