#include "gamemodel.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QImage>

GameModel::GameModel(QObject *parent)
    : QObject{parent},
    worldInitialized(false),
    timer(this),
    fishSpawnTimer(this)

{
    connect(&this->timer, &QTimer::timeout, this, &GameModel::updateWorld);
    connect(&this->fishSpawnTimer, &QTimer::timeout, this, &GameModel::spawnFish);

    connect(&this->timer, &QTimer::timeout, this, &GameModel::checkInvalidFish);
    timer.setInterval(10);

    world = new b2World(b2Vec2(0.0f, 0.0f));
    isholdingfish = false;
    paused = true;
}

void GameModel::speedup() {
    fishGenerationFrequency /= SPEEDUP_AMOUNT;
    conveyorSpeed *= SPEEDUP_AMOUNT;
    fishSpawnTimer.setInterval(fishGenerationFrequency);
    timeSinceLastSpawn.start();
}

void GameModel::checkInvalidFish() {
    vector<b2Body*> toRemove;

    for (auto [body, fish] : fishes.asKeyValueRange()) {
        b2Vec2 position = body->GetPosition();
        //int translateY = fish.imageHeight/2;
        // position.x + fish.imageWidth/2 > 980 + translateY || position.y > 510 + translateY || position.y + translateY < 0 - translateY
        if (fish.isOutOfBounds(position.x, position.y, 980, 650) && body != heldFish) {
            toRemove.push_back(body);
        }
    }

    for (b2Body* body : toRemove) {
        fishes.remove(body);
        emit wrongFish();
    }

}

void GameModel::beginWorldStep() {
    timer.start();

    // Initialize the conveyor belt params
    fishGenerationFrequency = INITIAL_FISH_GENERATION_FREQUENCY * SPEEDUP_AMOUNT;
    conveyorSpeed = INITIAL_CONVEYOR_SPEED / SPEEDUP_AMOUNT;
    speedup();
    fishSpawnTimer.start();

    togglePause(false);
}

void GameModel::reset() {
    emit resetComponent();
    this->fishes.clear();
    buckets.clear();
    worldInitialized = false;
    isholdingfish = false;
    timer.stop();
    b2World* tempworld = new b2World(b2Vec2(10,0));
    delete world;
    world = tempworld;
}

void GameModel::togglePause(bool paused) {
    this->paused = paused;
    if (paused) {
        timer.stop();
        fishSpawnTimer.stop();
    } else {
        timer.start();
        fishSpawnTimer.start();
    }
}

void GameModel::drop() {
    if (paused || isholdingfish == false)
        return;

    isholdingfish = false;
    heldFish->SetActive(true);
    for (b2Body* bucketBody : buckets.keys()) {
        bool collision = heldFishBucketOverlap(bucketBody);
        if (collision) {
            if (buckets[bucketBody].targetSpecies == fishes[heldFish].species)
            {
                emit correctFish();
            }
            else
            {
                emit wrongFish();
            }
            deleteFish(heldFish);
        }
    }
}

bool GameModel::heldFishBucketOverlap (b2Body* bucketBody) {
    b2Vec2 position = bucketBody->GetPosition();
    if (position.x < lastmousecoords.x && lastmousecoords.x < position.x + BOX_SIZE) {
        if (position.y < lastmousecoords.y && lastmousecoords.y < position.y + BOX_SIZE) {
            return true;
        }
    }

    return false;
}

void GameModel::spawnBucket(int x, int y, Species species) {
    b2BodyDef bucketBodyDef;
    bucketBodyDef.type = b2_staticBody;
    bucketBodyDef.position.Set(x, y);

    b2Body* body = world->CreateBody(&bucketBodyDef);

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

    body->SetUserData(&buckets[body]);
}

void GameModel::updateWorld() {
    if (!worldInitialized) {

        spawnBucket(25, 137, Species::Coho);
        spawnBucket(220, 137, Species::Sockeye);
        spawnBucket(415, 137, Species::Chinook);
        spawnBucket(605, 137, Species::Chum);
        spawnBucket(800, 137, Species::Pink);
        spawnWalls();

        worldInitialized = true;
        emit worldInit();
    }

    // It is generally best to keep the time step and iterations fixed.
    if (isholdingfish) {
        b2Vec2 transformedheldfishcoords(heldfishcoords.x+heldFish->GetPosition().x, heldfishcoords.y + heldFish->GetPosition().y);
        // TODO: Remove this:
        heldFish->ApplyLinearImpulse(1000*b2Vec2(lastmousecoords.x-transformedheldfishcoords.x, lastmousecoords.y-transformedheldfishcoords.y), heldFish->GetWorldCenter(), false);
        //cout << "x: " << event->position().x()-transformedheldfishcoords.x << " y: " << event->position().y()-transformedheldfishcoords.y << endl;
        heldFish->SetTransform(b2Vec2(lastmousecoords.x-heldfishcoords.x, lastmousecoords.y-heldfishcoords.y), 0);
        qDebug() << lastmousecoords.x << " " << lastmousecoords.y;
    }
    for (auto f = fishes.keyBegin(); f != fishes.keyEnd(); f++) {
        if ((*f)->GetLinearVelocity().x < conveyorSpeed)
            (*f)->SetLinearVelocity(b2Vec2(conveyorSpeed, (*f)->GetLinearVelocity().y));
    }
    world->Step(1.0/60.0, 6, 2);
    emit worldUpdated();
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
    if (timeSinceLastSpawn.elapsed() >= SPEEDUP_FREQUENCY) {
        speedup();
    }

    Species species = this->generateRandomSpecies();
    Fish fishy(this, species);

    b2BodyDef fishBodyDef;
    fishBodyDef.type = b2_dynamicBody;
    fishBodyDef.gravityScale = 0;

    b2Body* body = world->CreateBody(&fishBodyDef);
    b2PolygonShape polygon;
    int imageScalar = QRandomGenerator::global()->bounded(50, 60);

    polygon.SetAsBox(3 * imageScalar, imageScalar);
    fishy.imageHeight = imageScalar;
    fishy.imageWidth =  3 * imageScalar;

    // Generate x and y coordinates within the conveyor belt
    int dy = QRandomGenerator::global()->bounded(CONVEYOR_BELT_AREA.height() - fishy.imageHeight);
    int x = CONVEYOR_BELT_AREA.x() - fishy.imageWidth;
    int y = CONVEYOR_BELT_AREA.y() + dy;
    body->SetTransform(b2Vec2(x, y), 0);

    b2FixtureDef fixture;
    fixture.shape = &polygon;
    // Set the box density to be non-zero, so it will be dynamic.
    fixture.density = 1.0f;

    // Override the default friction.
    fixture.friction = 0.3f;
    fixture.restitution = 0.9;

    // Add the shape to the body.
    body->CreateFixture(&fixture);

    this->fishes.insert(body, fishy);

    body->SetUserData(&fishes[body]);
}

void GameModel::deleteFish(b2Body* fish) {

    if (world->GetBodyCount() > 0)
        world->DestroyBody(fish);

    fishes.remove(fish);
}

void GameModel::endGame()
{
    reset();
    togglePause(true);
}

void GameModel::spawnWalls() {
    b2BodyDef wallbodydef;
    wallbodydef.type = b2_staticBody;
    b2Body* body = world->CreateBody(&wallbodydef);

    b2PolygonShape polygon;
    //fix coords
    polygon.SetAsBox(1000.0f,50.0f);

    b2FixtureDef fixture;
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);
    body->SetTransform(b2Vec2(0,600),0);

    body = world->CreateBody(&wallbodydef);
    /*
    polygon.SetAsBox(10.0f,550.0f);
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);
    body->SetTransform(b2Vec2(0,0),0);
    */
}














