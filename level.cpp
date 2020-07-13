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

#include "globalvariables.h"
#include "projectile.h"
#include "userinput.h"

Level::Level(QObject* parent, QPointF initDim):
    QGraphicsScene(parent),
    sceneDim(initDim)
{
}


void Level::initPlayField() {
    m_groundLevel=987;
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(1.0,-10.0));

    // Set up all Background Objects
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/sky.png").scaled(3840,1080), QPointF(0.0,0.0), -400, -2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/bg.png"), QPointF(0.0,0.0), 100.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/Table.png").scaled(250,200),
                                      QPointF(1000, m_groundLevel -200), 200.0,-0.5, bgItems[1]));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/lamp.png"),
                                      QPointF(1000.0,0.0), 800.0, -0.5));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/lamp.png"), QPointF(2000.0,0.0), 800.0, -0.5));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/Table.png").scaled(350,300),
                                      QPointF(2000, m_groundLevel -100), 1200.0, 4));

    QVectorIterator<BackgroundItem*> bgIt(bgItems);
    while (bgIt.hasNext()) {
        addItem(bgIt.next());
    }


    // [Ground, Walls & other static objects]
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png"), QPointF(0,m_groundLevel),0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10,conv::sceneHeight), QPointF(-10,0),0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10,conv::sceneHeight), QPointF(conv::sceneWidth,0),0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(conv::sceneWidth,10), QPointF(0,-10),0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Person_2.png").scaled(200,600), QPoint(2500.0,700.0),0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Person_5.png").scaled(150,450), QPoint(1200.0,600.0),0, world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        sObj->setZValue(2);
        addItem(sObj);
    }

    // [Dynamic Objects]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(50,50), QPointF(790,0), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(100,150), QPointF(810,300), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(200,200), QPointF(740,600), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(100,400), QPointF(1500,60), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_5.png").scaled(150,350), QPointF(1450,0), world));
    //dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(100,200), QPointF(400,200), world));
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    //forceObjects.append(new ForceObject(QPixmap(""), QPointF(1,2), world, m_projectile));


    // [GOAL]
    m_goal = new Goal(QPixmap(":/imgs/png/Person_1.png").scaled(150,450));
    m_goal->setTransform(QTransform::fromScale(-1, 1));
    m_goal->setPos(3500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);


    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/flieger.png").scaled(200, 100), QPointF(400,400), world);
    addItem(m_projectile);


    // [USER INPUT]
    //m_input = new UserInput(m_projectile);

    // [VIEW WINDOW]
    viewportSetup();
    this->startTimer(10);
    view->show();
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
    world->Step(1/100.0, 6, 6);
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()) {
        DynamicObject* obj = dynIt.next();
        obj->updatePos(obj->getPos());
        obj->updateRot(obj->getRot());
    }
    m_projectile->updatePos((m_projectile->getPos()));
    m_projectile->updateRot((m_projectile->getRot()));
    updateView();
    //qreal newX = qBound(conv::xBoundary, m_projectile->pos().x(), this->sceneRect().bottomRight().x()-1920 + 900) - 1000.0;
    //view->setSceneRect(newX,0,1920,1080);

    // iterate and apply parallax for all background items
    //QVectorIterator<BackgroundItem*> i(bgItems);
    //while (i.hasNext())
    //    applyParallax(newX, i.next());

    checkColliding();
}

void Level::mousePressEvent(QGraphicsSceneMouseEvent* event){
    m_projectile->shoot();
}


void Level::applyParallax(qreal xPos, BackgroundItem* item) {
    item->setX(item->getPos().x() - item->getOffset()*((xPos/width())));
}

void Level::checkColliding() {
    for (QGraphicsItem* item : collidingItems(m_projectile)) {
        if (Goal* target = qgraphicsitem_cast<Goal*>(item)) {
            target->explode();
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
        case Qt::Key_A:
            m_projectile->shoot(b2Vec2(-5,3.0));
            break;
        case Qt::Key_S:
            m_projectile->shoot(b2Vec2(5,3.0));
            break;
        default:
            break;
    }
}


void Level::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_A:
            break;
        case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}

void Level::updateView() {
    qreal newX = qBound(0.0,
                        m_projectile->pos().x() - conv::xBoundary,
                        this->sceneRect().right()- conv::viewWidth + 900 - conv::xBoundary);
    qreal newY = qBound(0.0,
                        m_projectile->pos().y() - conv::viewHeight + conv::yBoundary,
                        this->sceneRect().bottom() - conv::viewHeight);

    view->setSceneRect(newX,newY,1920,1080);

    QVectorIterator<BackgroundItem*> i(bgItems);
    while (i.hasNext())
        applyParallax(newX, i.next());
}