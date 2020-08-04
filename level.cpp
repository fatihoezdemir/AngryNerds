#include "level.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPen>
#include <iostream>
#include <QtMath>
#include "goal.h"
#include "backgrounditem.h"
#include "staticobject.h"
#include "globalvariables.h"
#include "projectile.h"

Level::Level(QObject* parent, QPointF initDim):
    QGraphicsScene(parent),
    initProj(QPointF((conv::sceneWidth / 2.0) - 1600 ,conv::sceneHeight / 2.0)),
    sceneDim(initDim), arrowDragged(false), mouseReleased(false), viewOffset(0)
{
     win_timer = new QTimer();
}


void Level::initPlayField() {
    m_groundLevel=987;
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(0,-10.0));

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
    //dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(100,150), QPointF(810,300), world));
    //dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(200,200), QPointF(740,600), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(100,400), QPointF(1500,60), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_5.png").scaled(150,350), QPointF(1450,0), world));
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    forceFields.append(new ForceField(QPixmap(":imgs/png/CVL/CVL_beamer.png"), QPointF(1500,400),
                           0, b2Vec2(10,10)));
    addItem(forceFields[0]);

    // [GOAL]
    m_goal = new Goal(QPixmap(":/imgs/png/Person_1.png").scaled(150,450));
    m_goal->setTransform(QTransform::fromScale(-1, 1));
    m_goal->setPos(3500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/flieger.png").scaled(200, 100), Projectile::PLANE, initProj, world, nullptr);
    m_projectile->setTransformOriginPoint(m_projectile->boundingRect().width() / 2.0, m_projectile->boundingRect().height() / 2.0);
    m_projectile->setZValue(10);
    addItem(m_projectile);

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


void Level::timerEvent ( QTimerEvent* event )
{
    // Update Box2D World Collisions
    world->Step(1/100.0, 6, 6);

    // Update Position of Dynamic Objects
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()) {
        DynamicObject* obj = dynIt.next();
        obj->updatePos(obj->getPos());
        obj->updateRot(obj->getRot());
    }

    QVectorIterator<DynamicObject*> movingIt(movingObjects);
    while(movingIt.hasNext()) {
        DynamicObject* obj = movingIt.next();
        obj->oscPos();
        obj->updatePos(obj->getPos());
        obj->updateRot(obj->getRot());
    }

    // Update Position and Angle of Projectile
    m_projectile->updatePos((m_projectile->getPos()));
    m_projectile->updateRot((m_projectile->getRot()));

    if(arrowDragged){
        arrowLine->setLine((m_projectile->pos().x() + m_projectile->boundingRect().width() / 2.0) - 20,
                            (m_projectile->pos().y() + m_projectile->boundingRect().height() / 2.0) + 20,
                            m_projectile->pos().x() + m_projectile->boundingRect().width() / 2.0 + (QCursor::pos().x() - arrowInitX),
                            m_projectile->pos().y() + m_projectile->boundingRect().height() / 2.0 + (QCursor::pos().y() - arrowInitY));


        shootingAngle =  qRadiansToDegrees(qAtan((QCursor::pos().y() - arrowInitY) / (arrowInitX - QCursor::pos().x())));
        qreal deltaY = QCursor::pos().y() - arrowInitY;
        qreal deltaX = arrowInitX - QCursor::pos().x();
        if(deltaY > 0 && deltaX < 0) shootingAngle += 180.0;
        else if(deltaY < 0 && deltaX < 0) shootingAngle += 180.0;
        else if(deltaY < 0 && deltaX > 0) shootingAngle += 360.0;
        m_projectile->updateRot(-shootingAngle - 10);

        arrowDot->setPos((initProj.x() + m_projectile->boundingRect().width() / 2.0) + (QCursor::pos().x() - arrowInitX) - 345,
                          initProj.y() + m_projectile->boundingRect().height() / 2.0 + (QCursor::pos().y() - arrowInitY) - 565);  //offset of roundabout (150,150), not compensateable in the function-argument
    }

    // Update Viewport position and Parallax
    updateView();

    // Check for Collisions for Target and Sound
    checkColliding();
    checkFinish();
    m_projectile->checkVelocity();
}

void Level::checkFinish(){

}


void Level::applyParallax(qreal xPos, BackgroundItem* item) {
    item->setX(item->getPos().x() - item->getOffset()*((xPos/width())));
}

void Level::checkColliding() {
    for (QGraphicsItem* item : collidingItems(m_projectile)) {
            if (ForceField* field = qgraphicsitem_cast<ForceField*>(item)) {
                m_projectile->shoot(field->getField());
            }
            if (Goal* target = dynamic_cast<Goal*>(item)) {
                //QSound::play(":/sound/sound/nextLevel.wav");
                target->explode();
                //emit playerWin();
                win_timer->start(1000);
            }
    }
}

void Level::updateView() {
    qreal newX = qBound(0.0,
                        m_projectile->mapToScene(QPointF(100.0,50.0)).x()- conv::xBoundary,
                        this->sceneRect().right()- conv::viewWidth + 900 - conv::xBoundary);
    qreal newY = qBound(0.0,
                        m_projectile->mapToScene(QPointF(100.0,50.0)).y() - conv::yBoundary,
                        this->sceneRect().bottom() - conv::viewHeight);

    view->setSceneRect(newX,newY,1920,1080);

    QVectorIterator<BackgroundItem*> i(bgItems);
    while (i.hasNext())
        applyParallax(newX, i.next());
}

void Level::on_ProjectileTimeout() {
    emit playerDeath();
}


// arrow
void Level::mousePressEvent(QGraphicsSceneMouseEvent *event){
    arrowInitX = QCursor::pos().x();
    arrowInitY = QCursor::pos().y();

    viewOffset = 0.0;

    arrowDragged = true;

    arrowLine = new QGraphicsLineItem ((initProj.x() + m_projectile->boundingRect().width() / 2.0) - 20,
                                       (initProj.y() + m_projectile->boundingRect().height() / 2.0) + 20,
                                       initProj.x() + m_projectile->boundingRect().width() / 2.0 + (QCursor::pos().x() - arrowInitX),
                                       initProj.y() + m_projectile->boundingRect().height() / 2.0 + (QCursor::pos().y() - arrowInitY));
    arrowLine->setPen(QPen(Qt::red, 10));
    arrowLine->setZValue(0);
    addItem(arrowLine);


    arrowDot = new QGraphicsEllipseItem (initProj.x(), initProj.y(), 50, 50);
    arrowDot->setBrush(QBrush(Qt::red));
    arrowDot->setZValue(150);
    addItem(arrowDot);
}

void Level::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    arrowFinalX = QCursor::pos().x();
    arrowFinalY = QCursor::pos().y();

    arrowDragged = false;

    m_projectile->setTransformOriginPoint(0.0, 0.0);

    m_projectile->shoot(b2Vec2((arrowInitX - arrowFinalX)/50, (arrowFinalY - arrowInitY)/50));
    m_projectile->changeB2DRot(shootingAngle);
    arrowLine->hide();
    arrowDot->hide();
}


//adjust view position manually
void Level::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Left:
            viewOffset -= 200;
            break;
        case Qt::Key_Right:
            viewOffset += 200;
            break;
        case Qt::Key_Space:
            viewOffset = 0.0;
            break;
        default:
            break;
    }
}

void Level::levelOver(){
    emit playerWin();
}
