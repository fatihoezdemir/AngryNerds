#include "level.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPen>
#include "flieger.h"
#include "goal.h"
#include "backgrounditem.h"
#include "staticobject.h"

Level::Level(QObject* parent):
    QGraphicsScene(parent),
    m_minX(100),
    m_maxX(0),
    m_fieldWidth(3800),
    m_groundLevel(987),
    m_worldShift(0),
    m_velocity(20),
    m_wall(0),
    m_table(0),
    m_lamp(0),
    m_horizontalInput(0),
    m_jumpHeight(600)
{
    initPlayField();

    // Timer used for key control can be removed once physics engine is implemented
    m_timer.setInterval(10);
    connect(&m_timer, &QTimer::timeout, this, &Level::movePlayer);
}


void Level::initPlayField() {

    setSceneRect(0, 0, 3840, 1080); // Scene Dimensions

    m_sky = new BackgroundItem(QPixmap(":/imgs/png/sky.png").scaled(3800,1080), QPointF(0.0,0.0), -400);
    bgItems.append(m_sky);
    m_sky->setZValue(-3);
    addItem(m_sky);
    m_wall = new BackgroundItem(QPixmap(":/imgs/png/bg.png"), QPointF(0.0,0.0), 100.0);
    m_wall->setZValue(-2);
    bgItems.append(m_wall);
    addItem(m_wall);
    BackgroundItem* ground = new BackgroundItem(QPixmap(":/imgs/png/Floor.png"),
                                                QPointF(0,m_groundLevel), 0.0, m_wall);
    //ground->setPos(0, m_groundLevel);
    bgItems.append(ground);
    addItem(ground);
    m_table = new BackgroundItem(QPixmap(":/imgs/png/Table.png").scaled(250,200),
                                 QPointF(1000, m_groundLevel -200),
                                 200.0, m_wall);
    bgItems.append(m_table);
    addItem(m_table);
    m_lamp = new BackgroundItem(QPixmap(":/imgs/png/lamp.png"),
                                QPointF(1000.0,0.0), 800.0,
                                m_wall);
    bgItems.append(m_lamp);
    addItem(m_lamp);

    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/lamp.png"),
                                       QPointF(2000.0,0.0), 800.0,
                                       m_wall));
    addItem(bgItems.last());


    // static Objects
    staticObjects.append(new staticObject(QPixmap(":/imgs/png/Person_2.png").scaled(200,600), QPoint(2500.0,700.0)));
    staticObjects.append(new staticObject(QPixmap(":/imgs/png/Person_5.png").scaled(150,450), QPoint(1200.0,600.0)));
    QVectorIterator<staticObject*> it(staticObjects);
    while (it.hasNext())
    {
        staticObject* obj = it.next();
        obj->setZValue(2);
        addItem(obj);
    }

    // GOAL
    m_goal = new Goal(QPixmap(":/imgs/png/Person_1.png").scaled(150,450));
    m_goal->setTransform(QTransform::fromScale(-1, 1));
    m_goal->setPos(3500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    // PROJECTILE
    m_flieger = new Flieger();
    m_minX = m_flieger->boundingRect().width()*0.5;
    m_maxX = m_fieldWidth - m_flieger->boundingRect().width() * 0.5;
    m_flieger->setPos(m_minX, m_groundLevel - m_flieger->boundingRect().height() * 0.5);
    lastX= m_flieger->pos().x();
    m_currentX = m_minX;
    addItem(m_flieger);



    // Testing
    m_jumpAnimation = new QPropertyAnimation(this);
    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);


    // View Window
    viewportSetup();

}

void Level::viewportSetup(QRectF sceneRect, int height, int width){
    view = new QGraphicsView(this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(this);
    view->setFixedSize(width, height);
    view->setSceneRect(sceneRect);
}


// Timer not used yet, will be used with Box2D steps
void Level::timerEvent ( QTimerEvent* event )
{
}

void Level::applyParallax(qreal xPos, BackgroundItem* item) {
    item->setX(item->getPos().x() - item->getOffset()*((xPos/width())));
}

void Level::checkColliding() {
    for (QGraphicsItem* item : collidingItems(m_flieger)) {
        if (Goal* target = qgraphicsitem_cast<Goal*>(item)) {
            target->explode();
            //target->setTransform(QTransform::fromScale(-1, -1));
        }
    }
}

// These will be gone once the physics engine is put into place
void Level::keyPressEvent(QKeyEvent *event) {
    // Funtion reacts to keyboard input and moves plane
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

void Level::keyReleaseEvent(QKeyEvent *event)
{ // Deals also with keyboard Input
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

void Level::addHorizontalInput(int input) {
    // Keyboard input as well
    m_horizontalInput += input;
    m_flieger->setDirection(qBound(-1, m_horizontalInput, 1));
    checkTimer();
}

void Level::checkTimer() {
    // Timer for keyboard input
    if(m_flieger->direction() == 0) {
        m_timer.stop();
    } else if (!m_timer.isActive()) {
        m_timer.start();
    }
}

void Level::movePlayer()
{
    // move the plane
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
    newX = m_currentX - m_worldShift;
    m_flieger->setX(newX);

    newX = qBound(1000.0, this->m_flieger->pos().x(), this->sceneRect().bottomRight().x()-1920 + 900) - 1000.0;
    view->setSceneRect(newX,0,1920,1080);

    const qreal ratio = qreal(m_worldShift) / maxWorldShift;

    // iterate and apply parallax for all background items
    QVectorIterator<BackgroundItem*> i(bgItems);
    while (i.hasNext())
        applyParallax(newX, i.next());

    checkColliding();
}

void Level::setJumpFactor(const qreal &pos) {
    if (pos == m_jumpFactor) {
        return;
    }
    m_jumpFactor = pos;
    emit jumpFactorChanged(m_jumpFactor);

    qreal groundY = (m_groundLevel - m_flieger->boundingRect().height() / 2);
    qreal y = groundY - m_jumpAnimation->currentValue().toReal()*m_jumpHeight;
    m_flieger->setY(y);
}

void Level::jump() {
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
        m_jumpAnimation->start();
    }

}

qreal Level::jumpFactor() const
{
    return m_jumpFactor;
}



