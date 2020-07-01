#include <QApplication>
#include <QGraphicsView>
#include <QDateTime>
#include "bib.h"
#include "level.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QDateTime::currentMSecsSinceEpoch());

    Level scene;
    scene.view->show();
    return a.exec();
}
