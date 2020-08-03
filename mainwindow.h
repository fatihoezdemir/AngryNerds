#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <setting.h>
#include "level.h"
#include "cvl.h"
#include "level.h"
#include "logic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Level* l1;
    Cvl *l2;
private slots:

    void on_settings_button_clicked();
    void move_home();
    void on_bibliothek_button_clicked();
    void on_cvl_button_clicked();

    void on_cvl_lv_1_button_clicked();
    void on_cvl_lv_2_button_clicked();
    void on_cvl_lv_3_button_clicked();

    void on_mensa_lv_1_button_clicked();
    void on_mensa_lv_2_button_clicked();
    void on_mensa_lv_3_button_clicked();

    void on_bib_lv_1_button_clicked();
    void on_bib_lv_2_button_clicked();
    void on_bib_lv_3_button_clicked();

    void levelClose();

    void on_projektbeschreibung_clicked();

    void on_mensa_button_clicked();

private:
    bool is_open{false};
    Ui::MainWindow *ui;
    Setting _settings;

    Level::levelNum cvl_level;
    Level::levelNum mensa_level;
    Level::levelNum bib_level;

};

#endif // MAINWINDOW_H
