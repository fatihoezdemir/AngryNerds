#ifndef MENSA_H
#define MENSA_H
#include "level.h"
#include <QMediaPlayer>
#include <QMenuBar>

class Mensa : public Level
{
public:
    Mensa(levelNum lev = ONE, QObject* parent = nullptr, QPointF initDim = QPointF(8000,1500));
    virtual void initPlayField() override;
    void initLevel1();
    void initLevel2();
    void initLevel3();
};

#endif // MENSA_H
