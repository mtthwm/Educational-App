#include "gamemodel.h"
#include <QRandomGenerator>

GameModel::GameModel(QObject *parent)
    : QObject{parent}, world(b2Vec2(10.0f, 0.0f)),
    timer(this)
{

    connect(&this->timer, &QTimer::timeout, this, &GameModel::updateWorld);
    timer.start(10);
}

void GameModel::setHeight(int height) {
    this->height = height;
}

void GameModel::setWidth(int width) {
    this->width = width;
}

void GameModel::updateWorld() {
    world.Step(1.0/60.0, 6, 2);
    emit worldUpdated(fish);
}

void GameModel::spawnFish() {

}
