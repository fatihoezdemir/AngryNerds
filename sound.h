#ifndef SOUND_H
#define SOUND_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Sound; }
QT_END_NAMESPACE

class Sound : public QMainWindow
{
    Q_OBJECT

public:
    Sound(QWidget *parent = nullptr);
    ~Sound();

private:
    Ui::Sound *ui;
};
#endif // SOUND_H
