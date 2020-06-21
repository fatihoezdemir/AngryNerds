#include "widget.h"
#include "ui_widget.h"
#include <QTransform>
#include <QHBoxLayout>
#include <QGraphicsEllipseItem>
#include <QTimer>


//box2d (meters) to Qt (pixels) ratio: 1 meter = 30 pixels

Widget::Widget ( QWidget* parent ) :
QWidget ( parent ),
ui ( new Ui::Widget )
{
    ui->setupUi ( this );
    balls.resize(1);
    QTransform transform;
    scene = new QGraphicsScene;
    scene->setSceneRect ( 0, 0, 1600 , 1100 );
    scene->addRect(QRect(0,0,1600,1100),QPen(Qt::black));
    view = new QGraphicsView ( scene );
    view->setFixedSize ( 1700, 1200 );
    transform.reset();
    transform.scale ( 1  , -1 );
    view->setTransform ( transform );

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget ( view );
    this->setLayout ( layout );

    b2Vec2 gravity ( 0.0f, -10.0f );
    world = new b2World ( gravity );

    createWall();
    //this->startTimer ( 1000 / 60 );
}

Widget::~Widget()
{
    delete world;
    delete ui;
}

void Widget::timerEvent ( QTimerEvent* event )
{
    world->Step ( 1.0f / 60.0f, 8, 3 );
    QGraphicsEllipseItem* item =(QGraphicsEllipseItem* ) balls[0]->GetUserData();
    item->setPos(balls[0]->GetPosition().x*30,balls[0]->GetPosition().y*30);
    QWidget::timerEvent ( event );
}

void Widget::createWall()
{
    //groundBody
    b2BodyDef groundBodyDef;
    //groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set ( (-50 + scene->sceneRect().width()/2)/30.0  , -45/30.0 ); // gives middle point of box
                                                                                          // x-Axis: -50 since view is 100 = 2*50 pixels bigger than rect although it actually should be +50....y-Axis does not seem to have this issue
                                                                                          // y-Axis: -45 corresponds to ballRadius -> collision detection seems to work like for dynamic objects (like the balls) the outer shape
                                                                                          //         counts but for static objects (like the walls) only the middle point of the dynamic object can be detected from the static object
                                                                                          //         -> maybe the walls need to be defined as "b2_staticBody"?
                                                                                          // -> considering all the wall shiftings the whole b2 rect is moved like: (-45, -45), why?
    b2Body* groundBody = world->CreateBody ( &groundBodyDef );
    b2PolygonShape groundBox;
    groundBox.SetAsBox ( 800/30.0  , 0/30.0 ); // gives box`s half properties
    groundBody->CreateFixture ( &groundBox, 0.0f );
    QGraphicsRectItem* groundItem = new QGraphicsRectItem ( -10 , -10, 20 + scene->sceneRect().width(), 10 );
    groundItem->setBrush ( QBrush ( Qt::black ) );
    groundBody->SetUserData ( groundItem );
    scene->addItem ( groundItem );

    //topBody
    b2BodyDef topBodyDef;
    topBodyDef.position.Set ( (-50 + scene->sceneRect().width()/2)/30.0  , 1055/30.0 );
    b2Body* topBody = world->CreateBody ( &topBodyDef );
    b2PolygonShape topBox;
    topBox.SetAsBox ( 800/30.0  , 0/30.0 ); // gives box`s properties
    topBody->CreateFixture ( &topBox, 0.0f );
    QGraphicsRectItem* topItem = new QGraphicsRectItem ( -10, 1100, 20 + scene->sceneRect().width(), 10 );
    topItem->setBrush ( QBrush ( Qt::black ) );
    topBody->SetUserData ( topItem );
    scene->addItem ( topItem );

    //leftWallBody
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set (-45/30.0, scene->sceneRect().height()/2/30.0);
    b2Body* leftWallBody = world->CreateBody ( &leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox ( 1/30, 550/30.0 );
    leftWallBody->CreateFixture ( &leftWallBox, 0.0f );
    QGraphicsRectItem* leftWallItem = new QGraphicsRectItem ( -10, 0, 10, scene->sceneRect().height());
    leftWallItem->setBrush ( QBrush ( Qt::black ) );
    leftWallBody->SetUserData ( leftWallItem );
    scene->addItem ( leftWallItem );

    //rightWallBody
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set (1555/30.0, scene->sceneRect().height()/2/30.0);
    b2Body* rightWallBody = world->CreateBody ( &rightWallBodyDef);
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox ( 1/30, 550/30.0 );
    rightWallBody->CreateFixture ( &rightWallBox, 0.0f );
    QGraphicsRectItem* rightWallItem = new QGraphicsRectItem ( 1600, 0, 10, scene->sceneRect().height());
    rightWallItem->setBrush ( QBrush ( Qt::black ) );
    rightWallBody->SetUserData ( rightWallItem );
    scene->addItem ( rightWallItem );
}



void Widget::createBall()
{

    QGraphicsEllipseItem * ballItem;
    b2BodyDef ball;

    ball.type = b2_dynamicBody;
    ball.linearDamping = 0.01;
    ball.position.Set ( (50+10)/30.0 , (600-30)/30.0  );
    balls [0] =  world->CreateBody ( &ball );
    ballItem = new QGraphicsEllipseItem(0,0,1*90,1*90);
    ballItem->setBrush(Qt::red);
    ballItem->setPos((50+10) , 600-30 );
    scene->addItem(ballItem);
    balls[0]->SetUserData(ballItem);

    b2CircleShape ballShape;
    ballShape.m_p.Set(0,0);
    ballShape.m_radius = 45/30.0;
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.restitution = 0.8;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 13.0f;
    balls[0]->CreateFixture ( &ballFixtureDef );
    balls[0]->ApplyLinearImpulse( b2Vec2(1500, 1000), balls[0]->GetWorldCenter(), balls[0]->IsAwake() == true ); //initial impulse

}




void Widget::mousePressEvent(QMouseEvent *event){
    this->startTimer ( 1000 / 60 );
    createBall();
}
