#ifndef BIB_H
#define BIB_H

#include "level.h"
#include <QMediaPlayer>
#include <QMenuBar>

/*
 * The Bib-Room classes which extends the level class.
*/

class Bib : public Level
{
public:
    Bib(levelNum lev = ONE, QObject* parent = nullptr, QPointF initDim = QPointF(8000,1500));
    virtual void initPlayField() override;
    void initLevel1();
    void initLevel2();
    void initLevel3();
};
#endif // BIB_H
