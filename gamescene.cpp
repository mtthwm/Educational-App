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
    model(this),
    fishImage(":/images/fish/coho.png"),
    bucketImage(":/images/bucket.png")
{
    ui->setupUi(this);


    connect(&model, &GameModel::worldUpdated, this, &GameScene::worldUpdated);
    //connect(&model, &GameModel::worldInit, this, &GameScene::worldInit);

    //QTimer::singleShot(12000, this, &GameScene::gameOver);
    //this was just to test the gameOver screen
    cout << model.fish.size() << endl;
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::worldInit() {
    model.beginWorldStep();
}

void GameScene::paintEvent(QPaintEvent *) {
    //cout << "paint event" << endl;
    QPainter painter(this);

    if (model.worldInitialized) {
        for (auto bucket = model.buckets.keyValueBegin(); bucket != model.buckets.keyValueEnd(); bucket++) {
            b2Vec2 position = (*bucket).first->GetPosition();
            painter.drawImage(position.x, position.y, bucketImage);
        }
    }

    for (auto fishBody = model.fish.keyValueBegin(); fishBody != model.fish.keyValueEnd(); fishBody++) {
        //cout << "draw fish" << endl;
        b2Vec2 position = (*fishBody).first->GetPosition();
        painter.drawImage((int)(position.x), (int)(position.y), getImage((*fishBody).second.variant, (*fishBody).second.species));
    }
    painter.end();
}

void GameScene::mousePressEvent(QMouseEvent *event) {
    for (auto fish = model.fish.keyValueBegin(); fish != model.fish.keyValueEnd(); fish++) {
        b2Vec2 position1 = (*fish).first->GetPosition();
        QImage fishimage = getImage((*fish).second.variant, (*fish).second.species);
        b2Vec2 position2(position1.x + fishimage.width(), position1.y + fishimage.height());

        //is within the box of the fish
        if (event->position().x() > position1.x &&
            event->position().x() < position2.x &&
            event->position().y() > position1.y &&
            event->position().y() < position2.y) {
            //cout << "position1(" << position1.x << ", " << position1.y << ")" << endl;
            //cout << "position2(" << position2.x << ", " << position2.y << ")" << endl;
            //cout << "mousepos(" << event->position().x() << ", " << event->position().y() << ")" << endl;

            model.heldFish = (*fish).first;
            model.heldfishcoords = b2Vec2(event->position().x()-position1.x, event->position().y()-position1.y);
            //cout << "heldfishcoords(" << heldfishcoords.x << ", " << heldfishcoords.y << ")" << endl;
            model.isholdingfish = true;
            model.lastmousecoords = b2Vec2(event->position().x(), event->position().y());
            //cout << "fish held" << endl;
            break;
        }
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *event) {
    model.lastmousecoords = b2Vec2(event->position().x(), event->position().y());
}

void GameScene::mouseReleaseEvent(QMouseEvent *) {
    //cout << "fish released" << endl;
    model.isholdingfish = false;
}



void GameScene::worldUpdated() {
    update();
}

QImage GameScene::getImage(int variant, int species) {
    return fishImage;
}

// This function is being moved to GameModel, but is being kept here to keep the app going.
/*
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
*/
