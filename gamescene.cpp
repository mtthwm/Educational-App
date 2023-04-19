#include "gamescene.h"
#include "ui_gamescene.h"
#include "Box2D/Box2D.h"
#include "Species.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QRandomGenerator>
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
    ui->menu->setVisible(false);
    connect(&model, &GameModel::resetComponent, this->ui->scoreBoard, &ScoreBoard::reset);
    connect(&model, &GameModel::worldUpdated, this, &GameScene::worldUpdated);
    connect(ui->menu, &EscapeMenu::exit, this, [=] {emit exit(); ui->menu->setVisible(false);});
    connect(ui->menu, &EscapeMenu::resume, this, [=] {model.togglePause(false); ui->menu->setVisible(false);});

    connect(this, &GameScene::drop, &model, &GameModel::drop);

    connect(&model, &GameModel::correctFish, this->ui->scoreBoard, &ScoreBoard::addScore);
    connect(&model, &GameModel::wrongFish, this->ui->scoreBoard, &ScoreBoard::addStrike);

    //QTimer::singleShot(12000, this, &GameScene::gameOver);
    //this was just to test the gameOver screen
    //cout << model.fish.size() << endl;
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::worldInit() {
    model.reset();
    model.beginWorldStep();
}

void GameScene::paintEvent(QPaintEvent *) {
    //cout << "paint event" << endl;
    QPainter painter(this);

    if (model.worldInitialized) {
        for (auto bucket = model.buckets.keyValueBegin(); bucket != model.buckets.keyValueEnd(); bucket++) {
            b2Vec2 position = (*bucket).first->GetPosition();

            QRectF rect((int)(position.x), (int)(position.y), model.BOX_SIZE, model.BOX_SIZE);
            painter.drawImage(rect, bucketImage);
        }
    }

    for (auto fishBody = model.fishes.keyValueBegin(); fishBody != model.fishes.keyValueEnd(); fishBody++) {
        //cout << "draw fish" << endl;
        b2Vec2 position = (*fishBody).first->GetPosition();
        int width = fishBody->second.imageWidth;
        int height = fishBody->second.imageHeight;
        //std::cout << height << ", " << width << endl;
        QRectF rect((int)(position.x), (int)(position.y), width, height);
        painter.drawImage(rect, getImage(fishBody->second));
    }
    painter.end();
}

void GameScene::mousePressEvent(QMouseEvent *event) {
    for (auto fish = model.fishes.keyValueBegin(); fish != model.fishes.keyValueEnd(); fish++) {
        b2Vec2 position1 = (*fish).first->GetPosition();

        //QImage fishimage = getImage((*fish).second.variant, (*fish).second.species);
        b2Vec2 position2(position1.x + fish->second.imageWidth, position1.y + fish->second.imageHeight);

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
    emit drop();
}

void GameScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        ui->menu->setVisible(!ui->menu->isVisible());
        model.togglePause(ui->menu->isVisible());
    }
}

void GameScene::worldUpdated() {
    update();
}

//TODO: add more images and then implement this function
QImage GameScene::getImage(const Fish& fish) {
    QString path;
    switch(fish.species) {

        case Species::Chinook:
            path = QString(":/images/fish/chinook%1.png").arg(1);
        break;


        case Species::Chum:
            path = QString(":/images/fish/chum%1.png").arg(1);
        break;


        case Species::Pink:
            path = QString(":/images/fish/pink%1.png").arg(1);
        break;


        case Species::Coho:
            path = QString(":/images/fish/coho%1.png").arg(1);
        break;


        case Species::Sockeye:
            path = QString(":/images/fish/sockeye%1.png").arg(1);
        break;

        default:
            path = QString(":/images/fish/coho%1.png").arg(1);
    }
    QImage image(path);
    return image;
}
