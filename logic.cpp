#include "logic.h"

Logic::Logic(location loc, Level::levelNum lev, QObject *parent)
    : QObject(parent), cur_loc(loc), cur_lev(lev)
{
    // Set Up the correct Level based on the users input in the GUI
    if (cur_loc == MENSA) {
        mensa_1 = new Mensa(cur_lev);
        mensa_1->view->show();
        connect(mensa_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(mensa_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
    } else if (cur_loc == CVL) {
        cvl_1 = new Cvl(cur_lev);
        cvl_1->view->show();
        connect(cvl_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(cvl_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
    } else if (cur_loc == BIB) {
        bib_1 = new Bib(cur_lev);
        bib_1->view->show();
        connect(bib_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(bib_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
    }

}

void Logic::restart() {
    // Restart the level if it was lost
    if (cur_loc == MENSA) {
        mensa_1->view->hide();
        delete mensa_1;
        mensa_1 = new Mensa(cur_lev);
        connect(mensa_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(mensa_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
        mensa_1->view->show();
    } else if (cur_loc == CVL) {
        cvl_1->view->hide();
        delete cvl_1;
        cvl_1 = new Cvl(cur_lev);
        connect(cvl_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(cvl_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
        cvl_1->view->show();
    } else if (cur_loc == BIB) {
        bib_1->view->hide();
        delete bib_1;
        bib_1 = new Bib(cur_lev);
        connect(bib_1 ,SIGNAL(playerDeath()), this,SLOT(restart()));
        connect(bib_1, SIGNAL(playerWin()), this, SLOT(nextLevel()));
        bib_1->view->show();
    }
}

void Logic::nextLevel(){
    // Load the next Level if the goal was hit
    if (cur_lev == Level::ONE) {
        cur_lev = Level::TWO;
    } else if (cur_lev == Level::TWO) {
        cur_lev = Level::THREE;
    }
    //restart();

    if (cur_loc == MENSA) {
        mensa_1->view->hide();
        delete mensa_1;
    } else if (cur_loc == CVL) {
        cvl_1->view->hide();
        delete cvl_1;
    } else if (cur_loc == BIB) {
        bib_1->view->hide();
        delete bib_1;
    }

    emit levelOver();
}
