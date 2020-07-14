#include "mensa.h"

Mensa::Mensa(QObject* parent, QPointF initDim)
    : Level(parent, initDim)
{
    initLevel1();
}

void Mensa::initPlayField(){
    // Initializes Background and all objects that stay the same

    m_groundLevel=sceneDim.y()-100; // Set ground level
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(0,-10.0));

    // Set up all Background Objects
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/sky.png").scaled(sceneDim.x(),sceneDim.y()),QPointF(0,0), -sceneDim.x()*0.2, -5));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/wall2.png").scaled(sceneDim.x(), 1200), QPointF(0, 0), 0, -3));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/floor.png").scaled(sceneDim.x(), 300), QPointF(0, sceneDim.y()-300), 0,-2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/Cart1.png"), QPointF(800,sceneDim.y() - 700), -100, -2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/Cart2.png"), QPointF(1700,sceneDim.y() - 800), -100, -2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/Cart3.png"), QPointF(4000,sceneDim.y() - 780), -100, -2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/Cart4.png"), QPointF(4900,sceneDim.y() - 780), -100, -2));
    for (int i = 0; i<5; i++) {
        bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(sceneDim.x()/5*(i+0.5),0), sceneDim.x()*0.1, -2));
        bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(sceneDim.x()/5*(i),0), sceneDim.x()*0.2, 2));
    }
    QVectorIterator<BackgroundItem*> bgIt(bgItems);
    while (bgIt.hasNext()) {
        addItem(bgIt.next());
    }
    // [Ground, Walls & other static objects]
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/mensa/floor2.png").scaled(sceneDim.x(), 100), QPointF(0,sceneDim.y()-100), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10, sceneDim.y()), QPointF(-10,0), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10,sceneDim.y()), QPointF(sceneDim.x(),0),10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(sceneDim.x(),10), QPointF(0,-10), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/mensa/kasse.png").scaled(500,500), QPointF(7000, 800), 0, world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        addItem(sObj);
    }

    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/mensa/Tomate.png").scaled(150,150), Projectile::TOMATO, QPointF(400,800), world);
    addItem(m_projectile);

    connect(m_projectile->outTimer,SIGNAL(timeout()), this,SLOT(on_ProjectileTimeout()));
}

void Mensa::initLevel1(){

    // Initialize Background and all objects that stay the same throughout the levels
    initPlayField();

    // [Dynamic Objects]
    qreal x = 3200;
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/CVL/CVL_Pult.png").scaled(400,300), QPointF(x,m_groundLevel - 300 ), world));
    // [TOMATOES]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x, m_groundLevel - 350 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+100, m_groundLevel - 400 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+200, m_groundLevel - 400 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+300, m_groundLevel - 400 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+50, m_groundLevel - 500 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+150, m_groundLevel - 500 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+250, m_groundLevel - 500 ), world));

    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_1.png").scaled(200,80), QPointF(1000,500), world));
    movingObjects.back()->setOscillation(QPointF(200.0,200),0.08);
    addItem(movingObjects.back());


    // [FORCE FIELDS]
    forceFields.append(new ForceField(QPixmap(":imgs/png/mensa/Salami.png").scaled(800,400), QPointF(2800,400), 0 ,b2Vec2(0.01,-0.5)));
    forceFields[0]->setOpacity(0.5);
    addItem(forceFields[0]);


    // [GOAL]
    m_goal = new Goal(QPixmap(":/imgs/png/CVL/prof.png").scaled(150,450));
    m_goal->setTransform(QTransform::fromScale(-1, 1));
    m_goal->setZValue(10);
    m_goal->setPos(sceneDim.x() - 400, m_groundLevel - m_goal->boundingRect().bottomLeft().y() - 20);
    addItem(m_goal);

    // [VIEW WINDOW]
    viewportSetup();
    //view->scale(1.5,1.5);
    this->startTimer(10);
}
