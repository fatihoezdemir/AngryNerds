#ifndef LOGIC_H
#define LOGIC_H
#include "level.h"
#include "mensa.h"
#include "cvl.h"
#include "bib.h"

#include <QObject>

/*
 * The logic class is responsible for handleing the gameplay, once the player wins or looses.
 * An instance of each room is held and the used levels are re-loaded when a player dies and the
 * next level is loaded when a player wins.
*/


class Logic : public QObject
{
    Q_OBJECT
public:
    // Data-Type for the available rooms
    enum location{BIB, CVL, MENSA};
    explicit Logic(location loc = Logic::MENSA, Level::levelNum lev = Level::ONE, QObject *parent = nullptr);

private:
    /// Hold a level of each room and the level number
    Mensa* mensa_1;
    Cvl* cvl_1;
    Bib* bib_1;
    location cur_loc;
    Level::levelNum cur_lev;

signals:
    void levelOver();
public slots:
    void restart();
    void nextLevel();
};

#endif // LOGIC_H
