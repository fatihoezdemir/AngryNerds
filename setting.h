#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
// Class for audio settings page (audio not implemented yet)
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

signals:
    void HomeClicked();

private slots:
    void on_home_button_clicked();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
