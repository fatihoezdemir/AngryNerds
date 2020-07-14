#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include <QMediaPlayer>
#include "level.h"
#include "globalvariables.h"
#include "cvl.h"
#include "mensa.h"
#include <iostream>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  qsrand(QDateTime::currentMSecsSinceEpoch());
   // QPixmap pixmap(":/imgs/png/Person_1.png");
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap(":/imgs/png/Person_1.png"));
    splash->show();

    //Level scene;
    //scene.initPlayField();
    Cvl scene;
    //Mensa scene;
    //scene.initPlayField();
    scene.view->show();
    return a.exec();
}