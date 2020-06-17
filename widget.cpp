
#include "widget.h"
#include "ui_widget.h"
#include <QTransform>
#include <QHBoxLayout>
#include <QGraphicsEllipseItem>
#include <QTimer>

Widget::Widget ( QWidget* parent ) :
QWidget ( parent ),
ui ( new Ui::Widget )
{
    ui->setupUi ( this );
    balls.resize(5);
    QTransform transform;
    scene = new QGraphicsScene;
    scene->setSceneRect ( 0, 0, 800 , 600 );
    scene->addRect(QRect(0,0,800,600),QPen(Qt::black));
    view = new QGraphicsView ( scene );
    view->setFixedSize ( 900, 700 );
    transform.reset();
    transform.scale ( 1  , -1 );
    view->setTransform ( transform );

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget ( view );
    this->setLayout ( layout );

    b2Vec2 gravity ( 0.0f, -10.0f );
    world = new b2World ( gravity );

    createWall();
    createBall();
    this->startTimer ( 1000 / 60 );
}

Widget::~Widget()
{
    delete world;
    delete ui;
}

void Widget::timerEvent ( QTimerEvent* event )
{
    world->Step ( 1.0f / 60.0f, 8, 3 );
    for(int i = 0; i <= 4;i++){
        QGraphicsEllipseItem* item =(QGraphicsEllipseItem* ) balls[i]->GetUserData();
        item->setPos(balls[i]->GetPosition().x*30,balls[i]->GetPosition().y*30);
    }
    QWidget::timerEvent ( event );
}

void Widget::createWall()
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set ( scene->sceneRect().width()/2/30.0  , -5/30.0 );
    b2Body* groundBody = world->CreateBody ( &groundBodyDef );
    b2PolygonShape groundBox;
    groundBox.SetAsBox ( scene->sceneRect().width()/2/30.0  , 5/30.0 );
    groundBody->CreateFixture ( &groundBox, 0.0f );
    QGraphicsRectItem* groundItem = new QGraphicsRectItem ( 0, 0, scene->sceneRect().width(), 10 );
    groundItem->setBrush ( QBrush ( Qt::red ) );
    groundBody->SetUserData ( groundItem );
    scene->addItem ( groundItem );
}

void Widget::createBall()
{

    QGraphicsEllipseItem * ballItem;
    b2BodyDef ball;
    for(int i = 0; i <= 4;i++){
        ball.type = b2_dynamicBody;
        ball.linearDamping = 0.1*i;
        ball.position.Set ( (50+100*i)/30.0 , 600/30.0  );
        balls [i] =  world->CreateBody ( &ball );
        ballItem = new QGraphicsEllipseItem(0,0,1*30,1*30);
        ballItem->setBrush(Qt::red);
        ballItem->setPos(50+100*i,600);
        scene->addItem(ballItem);
        balls[i]->SetUserData(ballItem);

        b2CircleShape ballShape;
        ballShape.m_p.Set(0,0);
        ballShape.m_radius = 1;
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.restitution = 0.2*i;
        ballFixtureDef.shape = &ballShape;
        ballFixtureDef.density = 13.0f;
        balls[i]->CreateFixture ( &ballFixtureDef );
    }
}
