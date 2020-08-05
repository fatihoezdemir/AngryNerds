#include "bib.h"

Bib::Bib(levelNum lev, QObject* parent, QPointF initDim)
    : Level(parent, initDim)
{
    if (lev == ONE) {
        initLevel1();
    } else if (lev == TWO) {
        initLevel2();
    } else if (lev == THREE) {
        initLevel3();
    }
}

void Bib::initPlayField(){
    // Initializes Background and all objects that stay the same

    m_groundLevel=sceneDim.y()-100; // Set ground level
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(0,-10.0));


    // Set up all Background Objects
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/sky.png").scaled(sceneDim.x(),sceneDim.y()),QPointF(0,0), -sceneDim.x()*0.2, -5));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/bg.png").scaled(sceneDim.x(), 1200), QPointF(0, 0), 0, -3));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/Floor.png").scaled(sceneDim.x(), 300), QPointF(0, sceneDim.y()-300), 0,-2));


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
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/CVL_Pult.png").scaled(400,400), QPointF(7000, m_groundLevel - 300), 0, world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        addItem(sObj);
    }

    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/ball.png").scaled(150,150), Projectile::TOMATO, initProj, world);
    m_projectile->setTransformOriginPoint(m_projectile->boundingRect().width() / 2.0, m_projectile->boundingRect().height() / 2.0);
    m_projectile->setZValue(100);
    addItem(m_projectile);
    connect(m_projectile->outTimer,SIGNAL(timeout()), this,SLOT(on_ProjectileTimeout()));
    connect(win_timer, SIGNAL(timeout()), this, SLOT(levelOver()));
}

void Bib::initLevel1(){
    m_level = Level::ONE;
    // Initialize Background and all objects that stay the same throughout the levels
    initPlayField();

    // [Dynamic Objects]
    qreal x = 3200;
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 1150,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 650,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 1550,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 2050,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 1800,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 1800,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Person_5.png").scaled(150,450), QPointF(x + 1000,m_groundLevel - 300 ), world));

    // [Moving Objects]
    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(150,450), QPointF(6700,m_groundLevel-450), world));
    movingObjects.back()->setOscillation(QPointF(200.0,0),0.002);
    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_4.png").scaled(150,450), QPointF(6900,m_groundLevel-450), world));
    movingObjects.back()->setOscillation(QPointF(200.0,0),0.002);
    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_5.png").scaled(150,500), QPointF(6500,m_groundLevel-500), world));
    movingObjects.back()->setOscillation(QPointF(400.0,0),0.01);
    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_3.png").scaled(150,550), QPointF(6100,m_groundLevel-550), world));
    movingObjects.back()->setOscillation(QPointF(200.0,0),0.03);

    QVectorIterator<DynamicObject*> movIt(movingObjects);
    while (movIt.hasNext()){
        addItem(movIt.next());
    }


    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/flieger.png").scaled(200,100), QPointF(x, m_groundLevel - 350 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+300, m_groundLevel - 400 ), world));

    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    forceFields.append(new ForceField(QPixmap(":imgs/png/mensa/Salami.png").scaled(800,400), QPointF(2800,400), 0 ,b2Vec2(0.01,-0.5)));
    forceFields[0]->setOpacity(0.5);

    QVectorIterator<ForceField*> forceIt(forceFields);
    while (forceIt.hasNext()){
        addItem(forceIt.next());
    }


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

void Bib::initLevel2(){
    m_level = Level::TWO;
    // Initialize Background and all objects that stay the same throughout the levels
    initPlayField();

    // [Dynamic Objects]
    qreal x = 3200;
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 1150,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 650,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 1550,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 2050,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 1800,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 1800,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Person_5.png").scaled(400,300), QPointF(x + 1800,m_groundLevel - 300 ), world));



    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/flieger.png").scaled(200,100), QPointF(x, m_groundLevel - 350 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+300, m_groundLevel - 400 ), world));

    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    forceFields.append(new ForceField(QPixmap(":imgs/png/mensa/Salami.png").scaled(800,400), QPointF(2800,400), 0 ,b2Vec2(0.01,-0.5)));
    forceFields[0]->setOpacity(0.5);

    QVectorIterator<ForceField*> forceIt(forceFields);
    while (forceIt.hasNext()){
        addItem(forceIt.next());
    }


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

void Bib::initLevel3(){
    m_level = Level::THREE;
    // Initialize Background and all objects that stay the same throughout the levels
    initPlayField();

    // [Dynamic Objects]
    qreal x = 3200;
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 1150,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 650,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x - 1550,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/chair.png").scaled(200,400), QPointF(x + 2050,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 900,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x - 1800,m_groundLevel - 300 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/Table.png").scaled(400,300), QPointF(x + 1800,m_groundLevel - 300 ), world));



    dynamicObjects.append(new DynamicObject(QPixmap(":/imgs/png/flieger.png").scaled(200,100), QPointF(x, m_groundLevel - 350 ), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(x+300, m_groundLevel - 400 ), world));

    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    forceFields.append(new ForceField(QPixmap(":imgs/png/mensa/Salami.png").scaled(800,400), QPointF(2800,400), 0 ,b2Vec2(0.01,-0.5)));
    forceFields[0]->setOpacity(0.5);

    QVectorIterator<ForceField*> forceIt(forceFields);
    while (forceIt.hasNext()){
        addItem(forceIt.next());
    }


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

