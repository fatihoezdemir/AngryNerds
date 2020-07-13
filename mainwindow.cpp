#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cvl.h"
#include "mensa.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap mypix(":/imgs/png/GUI/tum_map.png");
    ui->label_pic->setPixmap(mypix);
    ui->stackedWidget->insertWidget(1, &_settings);
    connect(&_settings, SIGNAL(HomeClicked()), this, SLOT(move_home()));
//    connect(ui->cvl_lv_1_button, SIGNAL(clicked(bool)), ui->cvl_lv_2_button,SLOT(setChecked(bool)));
    l2 = new Cvl();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settings_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::move_home()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_bibliothek_button_clicked()
{

}

void MainWindow::on_cvl_button_clicked()
{
    Cvl* lvl = new Cvl();
//    lvl->initPlayField();
    MainWindow::hide();
    lvl->view->show();
}

void MainWindow::on_projektbeschreibung_clicked()
{
    Mensa* lvl = new Mensa();
    lvl->initPlayField();
    MainWindow::hide();
    lvl->view->show();
}

void MainWindow::on_cvl_lv_1_button_clicked()
{
    ui->cvl_lv_2_button->setChecked(false);
    ui->cvl_lv_3_button->setChecked(false);
}

void MainWindow::on_cvl_lv_2_button_clicked()
{
    ui->cvl_lv_1_button->setChecked(false);
    ui->cvl_lv_3_button->setChecked(false);
}

void MainWindow::on_cvl_lv_3_button_clicked()
{
    ui->cvl_lv_2_button->setChecked(false);
    ui->cvl_lv_1_button->setChecked(false);
}


void MainWindow::on_mensa_lv_1_button_clicked()
{
    ui->mensa_lv_2_button->setChecked(false);
    ui->mensa_lv_3_button->setChecked(false);
}

void MainWindow::on_mensa_lv_2_button_clicked()
{
    ui->mensa_lv_1_button->setChecked(false);
    ui->mensa_lv_3_button->setChecked(false);
}

void MainWindow::on_mensa_lv_3_button_clicked()
{
    ui->mensa_lv_1_button->setChecked(false);
    ui->mensa_lv_2_button->setChecked(false);
}


void MainWindow::on_bib_lv_1_button_clicked()
{
    ui->bib_lv_2_button->setChecked(false);
    ui->bib_lv_3_button->setChecked(false);
}

void MainWindow::on_bib_lv_2_button_clicked()
{
    ui->bib_lv_1_button->setChecked(false);
    ui->bib_lv_3_button->setChecked(false);
}

void MainWindow::on_bib_lv_3_button_clicked()
{
    ui->bib_lv_1_button->setChecked(false);
    ui->bib_lv_2_button->setChecked(false);
}

