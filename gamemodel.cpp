#include "gamemodel.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QImage>

GameModel::GameModel(QObject *parent)
    : QObject{parent},
    worldInitialized(false),
    world(b2Vec2(10.0f, 0.0f)),
    timer(this)

{
    connect(&this->timer, &QTimer::timeout, this, &GameModel::updateWorld);
    timer.setInterval(10);
}

void GameModel::setHeight(int height) {
    this->height = height;
}

void GameModel::setWidth(int width) {
    this->width = width;
}

void GameModel::beginWorldStep() {
    timer.start();
}

void GameModel::reset() {

}

void GameModel::togglePause(bool paused) {
    this->paused = paused;
    if (paused)
        timer.stop();
    else
        timer.start();
}

void GameModel::spawnBucket(int x, int y, Species species) {
    b2BodyDef bucketBodyDef;
    bucketBodyDef.type = b2_staticBody;
    bucketBodyDef.position.Set(x, y);

    b2Body* body = world.CreateBody(&bucketBodyDef);

    // Create a shape for this sensor
    b2CircleShape circle;
    circle.m_radius = 20;

    // Add the shape to the body.
    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.isSensor = true;
    body->CreateFixture(&fixture);

    Bucket bucket(this, body, species);

    this->buckets.insert(body, bucket);
}

void GameModel::updateWorld() {
    if (!worldInitialized) {
        spawnBucket(100, 100, Species::Coho);
        worldInitialized = true;
        emit worldInit();
    }

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
