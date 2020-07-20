#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include <QMediaPlayer>
#include "level.h"
#include "globalvariables.h"
#include "cvl.h"
#include "mensa.h"
#include "mainwindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen;
    // splash->setPixmap(QPixmap(":/imgs/png/Person_1.png"));
    // splash->show();

    MainWindow w;
    w.show();
    return a.exec();
}
