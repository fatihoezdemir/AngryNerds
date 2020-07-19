#include "logic.h"

Logic::Logic(location loc, Level::levelNum lev, QObject *parent)
    : QObject(parent), cur_loc(loc), cur_lev(lev)
{
    mensa_1 = new Mensa(cur_lev);
    mensa_1->view->show();
    connect(mensa_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
    connect(mensa_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
}

void Logic::restart() {
    mensa_1->view->hide();
    delete mensa_1;
    mensa_1 = new Mensa(cur_lev);
    connect(mensa_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
    connect(mensa_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
    mensa_1->view->show();
}

void Logic::nextLevel(){
    if (cur_lev == Level::ONE) {
        cur_lev = Level::TWO;
    } else if (cur_lev == Level::TWO) {
        cur_lev = Level::THREE;
    }
    restart();
}
