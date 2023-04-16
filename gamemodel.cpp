#include "gamemodel.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QImage>

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

void GameModel::beginWorldStep() {

}

void GameModel::reset() {

}

void GameModel::togglePause(bool paused) {

}

void GameModel::spawnBucket() {

}

void GameModel::updateWorld() {
    world.Step(1.0/60.0, 6, 2);
    emit worldUpdated(fish);
}

Species GameModel::generateRandomSpecies() {
    int speciesChoice = QRandomGenerator::global()->generate() % 5;
    Species species = Species::None;
    switch (speciesChoice) {
        case 0:
            species = Species::Sockeye;
            break;
        case 1:
            species = Species::Pink;
            break;
        case 2:
            species = Species::Coho;
            break;
        case 3:
            species = Species::Chinook;
            break;
        case 4:
            species = Species::Chum;
            break;
        default:
            qDebug() << "Unreachable.";
            species = Species::None;
            break;
    }
    return species;
}

void GameModel::spawnFish() {
    Species species = this->generateRandomSpecies();
    Fish fish(this, species);
    b2BodyDef fishBodyDef;
    fishBodyDef.type = b2_dynamicBody;
    fishBodyDef.position.Set(QRandomGenerator::global()->generate() % width, QRandomGenerator::global()->generate() % height);
    fishBodyDef.gravityScale = (QRandomGenerator::global()->generate() % 20) / 10.0f;
    b2Body* body = world.CreateBody(&fishBodyDef);
    //b2PolygonShape polygon;
    //polygon.SetAsBox(fish.fishImage->width(), fish.fishImage->height());
    b2FixtureDef fixture;
    //fixture.shape = &polygon;
    // Set the box density to be non-zero, so it will be dynamic.
    fixture.density = 1.0f;

    // Override the default friction.
    fixture.friction = 0.3f;
    fixture.restitution = 0.9;

    // Add the shape to the body.
    body->CreateFixture(&fixture);
    this->fish.insert(body, fish);
}
