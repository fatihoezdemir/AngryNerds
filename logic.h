#ifndef LOGIC_H
#define LOGIC_H
#include "level.h"
#include "mensa.h"
#include "cvl.h"

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
public:
    enum location{BIB, CVL, MENSA};
    explicit Logic(location loc = Logic::MENSA, Level::levelNum lev = Level::ONE, QObject *parent = nullptr);


private:
    Mensa* mensa_1;
    Cvl* cvl_1;
    location cur_loc;
    Level::levelNum cur_lev;

signals:

public slots:
    void restart();
    void nextLevel();
};

#endif // LOGIC_H
