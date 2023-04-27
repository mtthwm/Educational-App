#include "gamescene.h"
#include "ui_gamescene.h"
#include "Box2D/Box2D.h"
#include "Species.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QRandomGenerator>

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene),
    model(this),
    bucketImage(":/images/bucket.png") {
    ui->setupUi(this);

    ui->exitButton->setVisible(false);

    connect(&model, &GameModel::resetComponent, this->ui->scoreBoard, &ScoreBoard::reset);
    connect(&model, &GameModel::worldUpdated, this, &GameScene::worldUpdated);

    connect (ui->exitButton, &QPushButton::clicked, this, &GameScene::exitGame);

    connect(this, &GameScene::drop, &model, &GameModel::drop);
    connect(this, &GameScene::exit, &model, &GameModel::endGame);

    connect(&model, &GameModel::correctFish, this->ui->scoreBoard, &ScoreBoard::addScore);

    connect(&model, &GameModel::correctFish, this, &GameScene::showPlusOne);
    connect(&model, &GameModel::wrongFish, this, &GameScene::showStrike);


    connect(&model, &GameModel::wrongFish, this->ui->scoreBoard, &ScoreBoard::addStrike);

    connect(ui->scoreBoard, &ScoreBoard::gameOver, &model, &GameModel::endGame);
    connect(ui->scoreBoard, &ScoreBoard::gameOver, this, &GameScene::gameOver);

    ui->plusOneIcon->setVisible(false);
    ui->strikeIcon->setVisible(false);
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
    QPainter painter(this);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);

    QRect backgroundrect(0,0,1000,650);
    painter.drawImage(backgroundrect, QImage(":/images/GameScene.png"));


    for (int i = 0; i <= (SCENEWIDTH-model.conveyorPosition * SCALE_FACTOR)/(model.CONVEYOR_DISTANCE * SCALE_FACTOR); i++) {
        int lineX = (model.conveyorPosition * SCALE_FACTOR) + (i*model.CONVEYOR_DISTANCE*SCALE_FACTOR);
        QRect line(lineX, 370, 10, 240);
        painter.fillRect(line, brush);
    }

    if (model.worldInitialized) {
        for (auto bucket = model.buckets.keyValueBegin(); bucket != model.buckets.keyValueEnd(); bucket++) {
            b2Vec2 position = SCALE_FACTOR * (*bucket).first->GetPosition();

            QRectF rect((int)(position.x), (int)(position.y), model.BOX_SIZE * SCALE_FACTOR, model.BOX_SIZE * SCALE_FACTOR);
            painter.drawImage(rect, bucketImage);
        }
    }



    for (auto fishBody = model.fishes.keyValueBegin(); fishBody != model.fishes.keyValueEnd(); fishBody++) {
        if (model.isholdingfish && fishBody->first == model.heldFish)
            continue;
        b2Vec2 position = SCALE_FACTOR * (*fishBody).first->GetPosition();
        int width = fishBody->second.imageWidth * SCALE_FACTOR;
        int height = fishBody->second.imageHeight * SCALE_FACTOR;
        QRectF rect((int)(position.x), (int)(position.y), width, height);
        painter.drawImage(rect, getImage(fishBody->second));
    }

    //draw held fish
    if (model.isholdingfish) {
        b2Vec2 position = SCALE_FACTOR * model.heldFish->GetPosition() - model.heldfishcoords;
        int width = SCALE_FACTOR * model.fishes[model.heldFish].imageWidth;
        int height = SCALE_FACTOR * model.fishes[model.heldFish].imageHeight;
        QRectF drawrect((int)(position.x), (int)(position.y), width*2, height*2);
        painter.drawImage(drawrect, getImage(model.fishes[model.heldFish]));
    }

    painter.end();
}

void GameScene::mousePressEvent(QMouseEvent *event) {
    for (auto fish = model.fishes.keyValueBegin(); fish != model.fishes.keyValueEnd(); fish++) {
        b2Vec2 position1 = (*fish).first->GetPosition();

        //QImage fishimage = getImage((*fish).second.variant, (*fish).second.species);
        b2Vec2 position2(position1.x + fish->second.imageWidth, position1.y + fish->second.imageHeight);

        position1 = SCALE_FACTOR * position1;
        position2 = SCALE_FACTOR * position2;

        //is within the box of the fish
        if (event->position().x() > position1.x &&
            event->position().x() < position2.x &&
            event->position().y() > position1.y &&
            event->position().y() < position2.y) {

            model.heldFish = (*fish).first;
            model.heldfishcoords = b2Vec2((event->position().x()-position1.x) / SCALE_FACTOR, (event->position().y()-position1.y) / SCALE_FACTOR);
            //disable collision
            model.heldFish->SetActive(false);
            model.isholdingfish = true;
            model.lastmousecoords = b2Vec2(event->position().x() / SCALE_FACTOR, event->position().y() / SCALE_FACTOR);
            break;
        }
    }
}

void GameScene::mouseMoveEvent(QMouseEvent *event) {
    model.lastmousecoords = b2Vec2(event->position().x() / SCALE_FACTOR, event->position().y() / SCALE_FACTOR);
}

void GameScene::mouseReleaseEvent(QMouseEvent *) {
    emit drop();
}

void GameScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        ui->exitButton->setVisible(!ui->exitButton->isVisible());
}

void GameScene::exitGame()
{
    ui->exitButton->setVisible(false);
    emit exit();
}

void GameScene::worldUpdated() {
    update();
}

QImage GameScene::getImage(const Fish& fish) {
    QString path;
    int variant = fish.variant;
    switch(fish.species) {

        case Species::Chinook:
            path = QString(":/images/fish/chinook%1.png").arg(variant);
        break;


        case Species::Chum:
            path = QString(":/images/fish/chum%1.png").arg(variant);
        break;


        case Species::Pink:
            path = QString(":/images/fish/pink%1.png").arg(variant);
        break;


        case Species::Coho:
            path = QString(":/images/fish/coho%1.png").arg(variant);
        break;


        case Species::Sockeye:
            path = QString(":/images/fish/sockeye%1.png").arg(variant);
        break;

        default:
            path = QString(":/images/fish/coho%1.png").arg(variant);
    }
    QImage image(path);
    return image;
}


void GameScene::showPlusOne()
{
    if (ui->strikeIcon->isVisible())
        ui->strikeIcon->setVisible(false);

    ui->plusOneIcon->setVisible(true);

    QTimer::singleShot(1000, ui->plusOneIcon, [=] {ui->plusOneIcon->setVisible(false);});
}

void GameScene::showStrike()
{
    if (ui->plusOneIcon->isVisible())
        ui->plusOneIcon->setVisible(false);

    ui->strikeIcon->setVisible(true);

    QTimer::singleShot(1000, ui->strikeIcon, [=] {ui->strikeIcon->setVisible(false);});
}
