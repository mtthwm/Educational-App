#include "gamescene.h"
#include "ui_gamescene.h"
#include "Box2D/Box2D.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include<iostream>

using std::cout;
using std::endl;

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene),
    world(b2Vec2(10.0f, 0.0f)),
    timer(this),
    fishImage(":/images/fish/coho.png")
{
    ui->setupUi(this);

    for (int i = 0; i < 10; i++) {
        spawnFish();
    }

    connect(&timer, &QTimer::timeout, this, &GameScene::updateWorld);
    timer.start(10);
    isholdingfish = false;
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);

    for (b2Body* fishBody : fishBodies) {
        b2Vec2 position = fishBody->GetPosition();
        painter.drawImage((int)(position.x), (int)(position.y), fishImage);
    }

    painter.end();
}

void GameScene::mousePressEvent(QMouseEvent *event) {
    for (b2Body* fishbody : fishBodies) {
        b2Vec2 position1 = fishbody->GetPosition();
        b2Vec2 position2(position1.x + fishImage.width(), position1.y + fishImage.height());

        //is within the box of the fish
        if (event->position().x() > position1.x &&
            event->position().x() < position2.x &&
            event->position().y() > position1.y &&
            event->position().y() < position2.y) {
            //cout << "position1(" << position1.x << ", " << position1.y << ")" << endl;
            //cout << "position2(" << position2.x << ", " << position2.y << ")" << endl;
            //cout << "mousepos(" << event->position().x() << ", " << event->position().y() << ")" << endl;

            heldFish = fishbody;
            heldfishcoords = b2Vec2(event->position().x()-position1.x, event->position().y()-position1.y);
            //cout << "heldfishcoords(" << heldfishcoords.x << ", " << heldfishcoords.y << ")" << endl;
            isholdingfish = true;
            lastmousecoords = b2Vec2(event->position().x(), event->position().y());
            //cout << "fish held" << endl;
            break;
        }
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *event) {
    lastmousecoords = b2Vec2(event->position().x(), event->position().y());
}

void GameScene::mouseReleaseEvent(QMouseEvent *) {
    //cout << "fish released" << endl;
    isholdingfish = false;
}

void GameScene::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    if (isholdingfish) {
        b2Vec2 transformedheldfishcoords(heldfishcoords.x+heldFish->GetPosition().x, heldfishcoords.y + heldFish->GetPosition().y);
        heldFish->ApplyLinearImpulse(1000*b2Vec2(lastmousecoords.x-transformedheldfishcoords.x, lastmousecoords.y-transformedheldfishcoords.y), heldFish->GetWorldCenter(), false);
        //cout << "x: " << event->position().x()-transformedheldfishcoords.x << " y: " << event->position().y()-transformedheldfishcoords.y << endl;
        heldFish->SetTransform(b2Vec2(lastmousecoords.x-heldfishcoords.x, lastmousecoords.y-heldfishcoords.y), 0);
    }
    world.Step(1.0/60.0, 6, 2);
    update();
}

void GameScene::spawnFish() {
    int uiWidth = this->width();
    int uiHeight = this->height();

    b2BodyDef fishBodyDef;
    fishBodyDef.type = b2_dynamicBody;
    fishBodyDef.position.Set(rand() % uiWidth, rand() % uiHeight);

    // TODO: Maybe we could vary gravity scale slightly to add variety
    // to the speeds at which fish come down the conveyor?
    fishBodyDef.gravityScale = (rand() % 20) / 10.0f;

    b2Body* fishBody = world.CreateBody(&fishBodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(fishImage.width(), fishImage.height());

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

    fishBodies.push_back(fishBody);
}
