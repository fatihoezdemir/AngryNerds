#include "sound.h"
#include "ui_sound.h"

Sound::Sound(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sound)
{
    ui->setupUi(this);
}

Sound::~Sound()
{
    delete ui;
}

