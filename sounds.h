#ifndef SOUNDS_H
#define SOUNDS_H

#include <QObject>
#include <QMediaPlayer>

//! Plays sound effects for certain events during the game
/*! There is one slot with an enumeration parameter such that various sounds can be played */

class SoundEngine : public QObject
{
    Q_OBJECT

public:

    //! Enumeration lisiting the available sounds
    enum eSound{borderCollisionSound=0, menuClickSound, backgroundSound, WonSound, nextLevelSound, TargetSound, TargetManSound, TargetWomanSound, RoundEndSound, ProjectileSound};

    //! Constructor, initializes a QMediaPlayer and sets the file paths
    SoundEngine()
        :
          borderCollision(new QMediaPlayer),
          menuClick(new QMediaPlayer),
          background(new QMediaPlayer),
          Won(new QMediaPlayer),
          nextLevel(new QMediaPlayer),
          Target(new QMediaPlayer),
          TargetMan(new QMediaPlayer),
          TargetWoman(new QMediaPlayer),
          Projectile(new QMediaPlayer)

    {
        borderCollision->setMedia(QUrl("qrc:/Sounds/TargetMissed.mp3"));
        menuClick->setMedia(QUrl("qrc:/Sounds/MenuClick.wav"));
        background->setMedia(QUrl("qrc:/Sounds/Background2.mp3"));
        Won->setMedia(QUrl("qrc:/Sounds/Won.wav"));
        nextLevel->setMedia(QUrl("qrc:/Sounds/nextLevel2.mp3"));
        Target->setMedia(QUrl("qrc:/Sounds/TargetHit.mp3"));
        TargetMan->setMedia(QUrl("qrc:/Sounds/WhenManHit.mp3"));
        TargetWoman->setMedia(QUrl("qrc:/Sounds/WhenWomanHit.mp3"));
        Projectile->setMedia(QUrl("qrc:/Sounds/PaperRelease.mp3"));


        borderCollision->setVolume(80);
        menuClick->setVolume(80);
        background->setVolume(80);
        Won->setVolume(80);
        nextLevel->setVolume(80);
        Target->setVolume(80);
        TargetMan->setVolume(80);
        TargetWoman->setVolume(80);
        Projectile->setVolume(80);

    }

    //! Destructor
    virtual ~SoundEngine(){};


public slots:

    //! Plays the sound that is requested by the enumeration parameter
    void playSound(int soundNumber)
    {
        switch(soundNumber)
        {
            case borderCollisionSound:
                borderCollision->play();
            break;

            case menuClickSound:
                menuClick->play();
            break;

            case backgroundSound:
                background->play();
            break;

            case WonSound:
                Won->play();
            break;

            case nextLevelSound:
                nextLevel->play();
            break;

            case TargetSound:
                Target->play();
            break;

            case TargetManSound:
                TargetMan->play();
            break;

            case TargetWomanSound:
                TargetWoman->play();
            break;

            case ProjectileSound:
                Projectile->play();
            break;

            default: break;

        }
    }

private:

    QScopedPointer<QMediaPlayer> borderCollision;
    QScopedPointer<QMediaPlayer> menuClick;
    QScopedPointer<QMediaPlayer> background;
    QScopedPointer<QMediaPlayer> Won;
    QScopedPointer<QMediaPlayer> nextLevel;
    QScopedPointer<QMediaPlayer> Target;
    QScopedPointer<QMediaPlayer> TargetMan;
    QScopedPointer<QMediaPlayer> TargetWoman;
    QScopedPointer<QMediaPlayer> Projectile;

};
#endif // SOUNDS_H

