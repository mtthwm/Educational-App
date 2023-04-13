#include "gamescene.h"
#include "ui_gamescene.h"

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this)
{
    ui->setupUi(this);

    world.SetGravity(b2Vec2(9.8f, 0.0f));

    b2BodyDef fishBodyDef;
    fishBodyDef.position.Set(0.4f, 05.5f);

    fishBody = world.CreateBody(&fishBodyDef);
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();


    painter.drawImage((int)(position.x*20), (int)(position.y*20), image);
    painter.drawImage(200, 200, image);
//    qDebug() << image;
    painter.end();
   }
void GameScene::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}
