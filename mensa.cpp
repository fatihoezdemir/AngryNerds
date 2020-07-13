#include "mensa.h"

Mensa::Mensa(QObject* parent, QPointF initDim)
    : Level(parent, initDim)
{
    initPlayField();
}

void Mensa::initPlayField(){
    m_groundLevel=sceneDim.y()-100;
    setSceneRect(0, 0, sceneDim.x(), sceneDim.y()); // Scene Dimensions

    world = new b2World(b2Vec2(1.0,-10.0));

    // Set up all Background Objects
    //bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/CVL/All.png").scaled(5000,2500), QPointF(0.0,0.0), -400, -2));
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
    bgItems[9]->setZValue(10);
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

    b2Vec2 vertices[3];
    vertices[0].Set(conv::p2m(-100.0), conv::p2m(-50, true));
    vertices[1].Set(conv::p2m(100), conv::p2m(50, true));
    vertices[2].Set(conv::p2m(-100), conv::p2m(-50, true));
    vertices[3].Set(conv::p2m(-100), conv::p2m(0, true));

    int32 count = 4;
    b2PolygonShape polygon;
    polygon.Set(vertices, count);

    //staticObjects.append(new StaticObject(QPixmap(":/imgs/png/flieger.png").scaled(200,100), polygon, QPoint(3400,1800), world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        //sObj->setZValue(2);
        addItem(sObj);
    }

    // [Dynamic Objects]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/CVL/CVL_Pult.png").scaled(400,300), QPointF(3800,m_groundLevel - 300 ), world));
    /*dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(100,150), QPointF(810,300), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Floor.png").scaled(200,200), QPointF(740,600), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(100,400), QPointF(1500,60), world));
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_5.png").scaled(150,350), QPointF(1450,0), world));*/
    //dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/Person_6.png").scaled(100,200), QPointF(400,200), world));
    QVectorIterator<DynamicObject*> dynIt(dynamicObjects);
    while (dynIt.hasNext()){
        addItem(dynIt.next());
    }

    // [FORCE FIELDS]
    //forceObjects.append(new ForceObject(QPixmap(""), QPointF(1,2), world, m_projectile));


    // [GOAL]
    m_goal = new Goal(QPixmap(":/imgs/png/CVL/prof.png").scaled(150,450));
    m_goal->setTransform(QTransform::fromScale(-1, 1));
    m_goal->setPos(4500, m_groundLevel - m_goal->boundingRect().bottomLeft().y());
    addItem(m_goal);

    b2Vec2 vertices2[3];
    vertices2[0].Set(conv::p2m(-100.0), conv::p2m(0, true));
    vertices2[1].Set(conv::p2m(100), conv::p2m(100, true));
    vertices2[2].Set(conv::p2m(-100), conv::p2m(0, true));
    vertices2[3].Set(conv::p2m(-100), conv::p2m(50, true));

    //int32 count = 4;
    b2PolygonShape polygon2;
    polygon2.Set(vertices2, count);

    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/flieger.png").scaled(200, 100), polygon2, QPointF(400,400), world);
    m_projectile = new Projectile(QPixmap(":/imgs/png/flieger.png").scaled(200, 100), QPointF(400,400), world);
    addItem(m_projectile);


    // [USER INPUT]
    //m_input = new UserInput(m_projectile);

    // [VIEW WINDOW]
    viewportSetup();
    this->startTimer(10);
}
