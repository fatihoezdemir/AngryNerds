#include "bib.h"
#include "backgrounditem.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QPen>
#include <QGraphicsPixmapItem>
#include "flieger.h"

Bib::Bib(QObject* parent):
    QGraphicsScene(parent),
    m_minX(0),
    m_maxX(0),
    m_fieldWidth(3800),
    m_groundLevel(987),
    m_worldShift(0),
    m_velocity(50),
    m_wall(0),
    m_table(0),
    m_lamp(0),
    m_horizontalInput(0),
    m_jumpHeight(600)
{
    initPlayField();
    m_timer.setInterval(30);
    connect(&m_timer, &QTimer::timeout, this, &Bib::movePlayer);
}

// Testing
void Bib::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Right:
            addHorizontalInput(1);
            break;
        case Qt::Key_Left:
            addHorizontalInput(-1);
            break;
        case Qt::Key_Space:
            jump();
            break;
        default:
            break;
    }
}

//Testing
void Bib::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Right:
        addHorizontalInput(-1);
        break;
    case Qt::Key_Left:
        addHorizontalInput(1);
        break;
        //    case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}

//Testing
void Bib::addHorizontalInput(int input) {
    m_horizontalInput += input;
    m_flieger->setDirection(qBound(-1, m_horizontalInput, 1));
    checkTimer();
}

//Testing
void Bib::checkTimer() {
    if(m_flieger->direction() == 0) {
        m_timer.stop();
    } else if (!m_timer.isActive()) {
        m_timer.start();
    }
}

void Bib::movePlayer()
{
    const int direction = m_flieger->direction();
    if (0 == direction) {
        return;
    }

    const int dx = direction * m_velocity;
    qreal newX = qBound(m_minX, m_currentX + dx, m_maxX);
    if (newX == m_currentX) {
        return;
    }
    m_currentX = newX;

    const int shiftBorder = 350;
    int rightShiftBorder = width() - shiftBorder;

    const int visiblePlayerPos = m_currentX - m_worldShift;
    const int newWorldShiftRight = visiblePlayerPos - rightShiftBorder;
    if (newWorldShiftRight > 0) {
        m_worldShift += newWorldShiftRight;
    }
    const int newWorldShiftLeft = shiftBorder - visiblePlayerPos;
    if (newWorldShiftLeft > 0) {
        m_worldShift -= newWorldShiftLeft;
    }
    const int maxWorldShift = m_fieldWidth - qRound(width());
    m_worldShift = qBound(0, m_worldShift, maxWorldShift);
    m_flieger->setX(m_currentX - m_worldShift);

    const qreal ratio = qreal(m_worldShift) / maxWorldShift;
    //applyParallax(ratio, m_wall);
    //applyParallax(ratio, m_table);
    //applyParallax(ratio, m_lamp);
    //applyParallax(ratio, m_coins);

    //checkColliding();
}

void Bib::applyParallax(qreal ratio, QGraphicsItem* item) {
    item->setX(-ratio * (item->boundingRect().width() - width()));
}



void Bib::initPlayField() {
    setSceneRect(0, 0, 3840, 1080);
    m_sky = new BackgroundItem(QPixmap(":/imgs/png/sky.png").scaled(3800,1080));
    m_sky->setPos(0,0);
    addItem(m_sky);
    m_wall = new BackgroundItem(QPixmap(":/imgs/png/bg.png"));
    addItem(m_wall);
    BackgroundItem* ground = new BackgroundItem(QPixmap(":/imgs/png/Floor.png"));
    addItem(ground);
    ground->setPos(0, m_groundLevel);
    m_table = new BackgroundItem(QPixmap(":/imgs/png/Table.png").scaled(250,200), m_wall);
    m_table->setPos(1500, m_groundLevel-200);
    addItem(m_table);
    m_lamp = new BackgroundItem(QPixmap(":/imgs/png/lamp.png"), m_wall);
    m_lamp->setPos(1000,0);
    addItem(m_lamp);


    m_flieger = new Flieger();
    m_minX = m_flieger->boundingRect().width() * 0.5;
    m_maxX = m_fieldWidth - m_flieger->boundingRect().width() * 0.5;
    m_flieger->setPos(m_minX, m_groundLevel - m_flieger->boundingRect().height() * 0.5);
    m_currentX = m_minX;
    addItem(m_flieger);

    m_jumpAnimation = new QPropertyAnimation(this);
    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

}


void Bib::setJumpFactor(const qreal &pos) {
    if (pos == m_jumpFactor) {
        return;
    }
    m_jumpFactor = pos;
    emit jumpFactorChanged(m_jumpFactor);

    qreal groundY = (m_groundLevel - m_flieger->boundingRect().height() / 2);
    qreal y = groundY - m_jumpAnimation->currentValue().toReal()*m_jumpHeight;
    m_flieger->setY(y);
}

void Bib::jump() {
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
        m_jumpAnimation->start();
    }

}

qreal Bib::jumpFactor() const
{
    return m_jumpFactor;
}
