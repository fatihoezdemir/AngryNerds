#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include <QMediaPlayer>
#include "level.h"
#include "globalvariables.h"
#include "cvl.h"
#include "mensa.h"
#include "logic.h"
#include <iostream>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap(":/imgs/png/Person_1.png"));
    splash->show();

    Logic* log = new Logic(Logic::MENSA, Level::TWO);
    return a.exec();
}
