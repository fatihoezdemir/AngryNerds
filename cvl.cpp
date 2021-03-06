#include "cvl.h"
#include "level.h"

Cvl::Cvl(levelNum lev, QObject* parent, QPointF initDim)
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

void Cvl::initPlayField(){
    /* Sets up Basic Playing Field;
     * The individual Level has to be loaded with initLevelX(); */
    m_groundLevel=sceneDim.y()-100;
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(1.0,-10.0));

    // Set up all Background Objects
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/VG2.png").scaled(sceneDim.x(),sceneDim.y()),QPointF(0,0), 0, -10));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG8.png").scaled(5350,3000), QPointF(0.0,0.0), 350.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG7.png").scaled(3500,350),QPointF(400, 930), 300.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG6.png").scaled(3500,550),QPointF(400, 945), 250.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG5.png").scaled(3500,350),QPointF(400, 1337), 200.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG3.png").scaled(2400,575),QPointF(1500, 1350), 150.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG2.png").scaled(2100,350),QPointF(1800, 1750), 100.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG1.png").scaled(1740,550),QPointF(2150, 1780), 50.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_HG2.png").scaled(1420,350),QPointF(2500, 2080), 100.0, -1));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/VG2.png").scaled(2750,1500),QPointF(0, 930), 10, 0));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/CVL_beamer.png").scaled(2750,1600), QPointF(2340.0,   350), -200, 3));

    QVectorIterator<BackgroundItem*> bgIt(bgItems);
    while (bgIt.hasNext()) {
        addItem(bgIt.next());
    }

    // [Ground, Walls & other static objects]

    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10, sceneDim.y()), QPointF(-10,0), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10,sceneDim.y()), QPointF(sceneDim.x(),0),10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(sceneDim.x(),10), QPointF(0,-10), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/CVL_Tafel.png").scaled(250,2250), QPoint(sceneDim.x() - 400,m_groundLevel - 2250), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(400,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(1000,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(1600,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(2200,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(2800,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(3400,0), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG1.png").scaled(500,1200), QPointF(0.0,930), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG3.png").scaled(380,600), QPointF(500,930), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG4.png").scaled(380,600), QPointF(880,980), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG5.png").scaled(380,600), QPointF(1260,1230), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG6.png").scaled(380,600), QPointF(1640,1430), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG7.png").scaled(380,600), QPointF(2020,1630), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG8.png").scaled(380,600), QPointF(2400,1830), 0, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/CVL/VG9.png").scaled(380,600), QPointF(2780,1870), 0, world));

    // [Floor]
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(sceneDim.x(), 100), QPointF(0,sceneDim.y()-100), 10, world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        //sObj->setZValue(2);
        addItem(sObj);
    }

    // [PROJECTILE]
    m_projectile = new Projectile(QPixmap(":/imgs/png/flieger.png").scaled(200, 100),
                                  Projectile::PLANE, QPointF(initProj.x(), initProj.y() - 20), world, nullptr);
    m_projectile->setTransformOriginPoint(m_projectile->boundingRect().width() / 2.0, m_projectile->boundingRect().height() / 2.0);
    m_projectile->setZValue(10);
    addItem(m_projectile);

    // Start level end timer
    connect(m_projectile->outTimer, SIGNAL(timeout()), this, SLOT(on_ProjectileTimeout()));
    connect(win_timer, SIGNAL(timeout()), this, SLOT(levelOver()));
}

void Cvl::initLevel1(){
    initPlayField(); // Initialize Background and all objects that stay the same

    // [Dynamic Objects]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/CVL/CVL_Pult.png").scaled(400,300), QPointF(3800,m_groundLevel - 300 ), world));
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
    m_goal->setPos(4500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    // [VIEW WINDOW]
    viewportSetup();
    this->startTimer(10);

}


void Cvl::initLevel2(){
    initPlayField(); // Initialize Background and all objects that stay the same

    // [Dynamic Objects]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/CVL/CVL_Pult.png").scaled(400,300), QPointF(3800,m_groundLevel - 300 ), world));
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/mensa/Tomate.png").scaled(100,100), QPointF(3600, m_groundLevel - 350 ), world));
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
    m_goal->setPos(4500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    // [VIEW WINDOW]
    viewportSetup();
    this->startTimer(10);

}

void Cvl::initLevel3(){
    initPlayField(); // Initialize Background and all objects that stay the same

    // [Dynamic Objects]
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
    m_goal->setPos(4500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(150,550), QPointF(3900,m_groundLevel - 500), world));
    movingObjects.back()->setOscillation(QPointF(200.0,0),0.009);
    movingObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_4.png").scaled(150,550), QPointF(3600,m_groundLevel - 500), world));
    movingObjects.back()->setOscillation(QPointF(200.0,0),0.002);

    QVectorIterator<DynamicObject*> movIt(movingObjects);
    while (movIt.hasNext()){
        addItem(movIt.next());
    }


    // [VIEW WINDOW]
    viewportSetup();
    this->startTimer(10);

}
