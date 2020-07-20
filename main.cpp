#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include <QMediaPlayer>
#include "level.h"
#include "globalvariables.h"
#include "cvl.h"
#include "mensa.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap(":/imgs/png/Person_1.png"));
    splash->show();

    //Level scene;
    //scene.initPlayField();
    //Cvl scene;
//    Mensa scene;
//    scene.initPlayField();
//    scene.view->show();
//    return a.exec();
    MainWindow w;
    w.show();
    return a.exec();
}
