#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include <QMediaPlayer>
#include "level.h"
#include "globalvariables.h"
#include "cvl.h"
#include "mensa.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QDateTime::currentMSecsSinceEpoch());

    //Level scene;
    //scene.initPlayField();
    Cvl scene;
    //Mensa scene;
    //scene.initPlayField();
    scene.view->show();
    return a.exec();
}
