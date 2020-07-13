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
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/sky.png").scaled(sceneDim.x(),sceneDim.y()),QPointF(0,0), -400, -5));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/wall2.png").scaled(sceneDim.x(), 1200), QPointF(0, 0), -300, -3));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/floor.png").scaled(sceneDim.x(), 300), QPointF(0, sceneDim.y()-300), 0,-2));
    bgItems.append(new BackgroundItem(QPixmap(":/imgs/png/mensa/Cart1.png"), QPointF(800,sceneDim.y() - 700), -100, -2));
    QVectorIterator<BackgroundItem*> bgIt(bgItems);
    while (bgIt.hasNext()) {
        addItem(bgIt.next());
    }
    // [Ground, Walls & other static objects]
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/mensa/floor2.png").scaled(sceneDim.x(), 100), QPointF(0,sceneDim.y()-100), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10, sceneDim.y()), QPointF(-10,0), 10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(10,sceneDim.y()), QPointF(sceneDim.x(),0),10, world));
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/Floor.png").scaled(sceneDim.x(),10), QPointF(0,-10), 10, world));
    for (int i = 0; i< 10; i++) {
        staticObjects.append(new StaticObject(QPixmap(":/imgs/png/lamp.png").scaled(200,300), QPoint(sceneDim.x()/10*(i+0.5),0), 0, world));
    }
    staticObjects.append(new StaticObject(QPixmap(":/imgs/png/mensa/Cart2.png"), QPointF(1600,sceneDim.y() - 800), 0, world));

    QVectorIterator<StaticObject*> it(staticObjects);
    while (it.hasNext())
    {
        StaticObject* sObj = it.next();
        //sObj->setZValue(2);
        addItem(sObj);
    }

    // [Dynamic Objects]
    dynamicObjects.append(new DynamicObject(QPixmap(":imgs/png/CVL/CVL_Pult.png").scaled(400,300), QPointF(3800,m_groundLevel - 300 ), world));
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

    // [PROJECTILE}
    m_projectile = new Projectile(QPixmap(":/imgs/png/mensa/Tomate.png").scaled(150, 150), QPointF(400,800), world, nullptr, true);
    addItem(m_projectile);


    // [USER INPUT]
    //m_input = new UserInput(m_projectile);

    // [VIEW WINDOW]
    viewportSetup();
    //view->scale(1.5,1.5);
    this->startTimer(10);
}
