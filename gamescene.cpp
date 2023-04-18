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
    connect(ui->menu, &EscapeMenu::exit, this, [=] {emit exit();});
    //connect(&model, &GameModel::worldInit, this, &GameScene::worldInit);

    //QTimer::singleShot(12000, this, &GameScene::gameOver);
    //this was just to test the gameOver screen
    //cout << model.fish.size() << endl;
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

    for (auto fishBody = model.fishes.keyValueBegin(); fishBody != model.fishes.keyValueEnd(); fishBody++) {
        //cout << "draw fish" << endl;
        b2Vec2 position = (*fishBody).first->GetPosition();
        painter.drawImage((int)(position.x), (int)(position.y), getImage((*fishBody).second.variant, (*fishBody).second.species));
    }
    painter.end();
}

void GameScene::mousePressEvent(QMouseEvent *event) {
    for (auto fish = model.fishes.keyValueBegin(); fish != model.fishes.keyValueEnd(); fish++) {
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

void GameScene::keyPressEvent(QKeyEvent *event) {
    cout << "keypressevent" << endl;
    if (event->key() == Qt::Key_Escape) {
        cout << "escape" << endl;
        ui->menu->setVisible(!ui->menu->isVisible());
    }
}

void GameScene::worldUpdated() {
    update();
}

//TODO: add more images and then implement this function
QImage GameScene::getImage(int variant, int species) {
    return fishImage;
}
