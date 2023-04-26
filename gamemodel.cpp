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
        if (fish.isOutOfBounds(position.x, position.y, 0.980f, 0.650f) && !isholdingfish) {
            toRemove.push_back(body);
        }

        if (position.y > CONVEYOR_BELT_AREA.height() + CONVEYOR_BELT_AREA.y() - 0.020f)
        {
            drop();
        }

    }

    for (b2Body* body : toRemove) {
        deleteFishAndBody(body);
        emit wrongFish();
    }

}

void GameModel::beginWorldStep() {
    timer.start();

    // Initialize the conveyor belt params
    fishGenerationFrequency = INITIAL_FISH_GENERATION_FREQUENCY * SPEEDUP_AMOUNT;
    conveyorSpeed = INITIAL_CONVEYOR_SPEED / SPEEDUP_AMOUNT;
    spawnFish();
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
    b2World* tempworld = new b2World(b2Vec2(0,0));
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

    QList keys = buckets.keys();

    for (b2Body* &bucketBody : keys) {
        bool collision = heldFishBucketOverlap(bucketBody);
        if (collision) {
            if (buckets[bucketBody] == fishes[heldFish].species)
            {
                emit correctFish();
            }
            else
            {
                emit wrongFish();
            }
            deleteFishAndBody(heldFish);
            return;
        }

    }
    if (lastmousecoords.y < CONVEYOR_BELT_AREA.y())
    {
        emit wrongFish();
        deleteFishAndBody(heldFish);
    }
    if (lastmousecoords.y > 0.600)
    {
        heldFish->SetTransform(b2Vec2(heldFish->GetPosition().x, 0.560), 0);
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

void GameModel::spawnBucket(float x, float y, Species species) {
    b2BodyDef bucketBodyDef;
    bucketBodyDef.type = b2_staticBody;
    bucketBodyDef.position.Set(x, y);

    b2Body* body = world->CreateBody(&bucketBodyDef);

//    // Create a shape for this sensor
//    b2CircleShape circle;
//    circle.m_radius = 20;

//    // Add the shape to the body.
//    b2FixtureDef fixture;
//    fixture.shape = &circle;
//    fixture.isSensor = true;
//    body->CreateFixture(&fixture);

    this->buckets.insert(body, species);

//    body->SetUserData(&buckets[body]);
}

void GameModel::updateWorld() {
    if (!worldInitialized) {

        spawnBucket(0.025f, 0.137f, Species::Coho);
        spawnBucket(0.220f, 0.137f, Species::Sockeye);
        spawnBucket(0.415f, 0.137f, Species::Chinook);
        spawnBucket(0.605f, 0.137f, Species::Chum);
        spawnBucket(0.800f, 0.137f, Species::Pink);
        spawnWalls();

        worldInitialized = true;
        emit worldInit();
    }

    // multipled by 1/60 because that's the time step
    conveyorPosition += conveyorSpeed/60;
    while (conveyorPosition >= CONVEYOR_DISTANCE) {
        conveyorPosition -= CONVEYOR_DISTANCE;
    }

    if (isholdingfish) {
        b2Vec2 transformedheldfishcoords(heldfishcoords.x+heldFish->GetPosition().x, heldfishcoords.y + heldFish->GetPosition().y);
        heldFish->SetTransform(b2Vec2(lastmousecoords.x-heldfishcoords.x, lastmousecoords.y-heldfishcoords.y), 0);
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
    Fish fish(this, species);

    b2BodyDef fishBodyDef;
    fishBodyDef.type = b2_dynamicBody;
    fishBodyDef.gravityScale = 0;

    b2Body* body = world->CreateBody(&fishBodyDef);
    b2PolygonShape polygon;
    float imageScalar = QRandomGenerator::global()->bounded(50, 60) / 1000.0f;

    polygon.SetAsBox(3 * imageScalar, imageScalar);
    fish.imageHeight = imageScalar;
    fish.imageWidth =  3 * imageScalar;

    // Generate x and y coordinates within the conveyor belt
    float dy = (CONVEYOR_BELT_AREA.height() - fish.imageHeight) * ((float) rand() / (float) RAND_MAX);
    float x = CONVEYOR_BELT_AREA.x() - fish.imageWidth;
    float y = CONVEYOR_BELT_AREA.y() + dy;
    body->SetTransform(b2Vec2(x, y), 0);

    b2FixtureDef fixture;
    fixture.shape = &polygon;
    // Set the box density to be non-zero, so it will be dynamic.
    fixture.density = 1.0f;

    // Override the default friction.
    fixture.friction = 0.3f;
    fixture.restitution = 0.9f;

    // Add the shape to the body.
    body->CreateFixture(&fixture);

    this->fishes.insert(body, fish);

    body->SetUserData(&fishes[body]);
}

void GameModel::deleteFishAndBody(b2Body* fish) {

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
    polygon.SetAsBox(CONVEYOR_BELT_AREA.width(),0.050f);

    //bottom conveyor wall
    b2FixtureDef fixture;
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);
    body->SetTransform(b2Vec2(CONVEYOR_BELT_AREA.x(),CONVEYOR_BELT_AREA.y() + CONVEYOR_BELT_AREA.height()), 0);

    //top conveyor wall
    body = world->CreateBody(&wallbodydef);
    fixture.shape = &polygon;
    body->CreateFixture(&fixture);
    body->SetTransform(b2Vec2(CONVEYOR_BELT_AREA.x(),CONVEYOR_BELT_AREA.y()-0.050),0);

}














