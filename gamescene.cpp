#include "gamescene.h"
#include "ui_gamescene.h"

#include <QPainter>

#include<iostream>

using std::cout;
using std::endl;

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene),
    world(b2Vec2(10.0f, 0.0f)),
    timer(this),
    fishImage(":/images/fish/coho1.jpg")
{
    ui->setupUi(this);

    b2BodyDef fishBodyDef;
    fishBodyDef.type = b2_dynamicBody;
    fishBodyDef.position.Set(0.4f, 5.5f);

    fishBody = world.CreateBody(&fishBodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;

    // Add the shape to the body.
    fishBody->CreateFixture(&fixtureDef);

    connect(&timer, &QTimer::timeout, this, &GameScene::updateWorld);
    timer.start(10);
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = fishBody->GetPosition();

    printf("%4.2f %4.2f", position.x, position.y);

    painter.drawImage((int)(position.x), (int)(position.y), fishImage);

    painter.end();
}

void GameScene::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}
