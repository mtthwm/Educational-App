#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include "bucket.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QHash>
#include <QRect>

using std::vector;


class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);

    QHash<b2Body*, Bucket> buckets;
    QHash<b2Body*, Fish> fishes;
    bool worldInitialized;
    b2Body* heldFish;
    b2Vec2 heldfishcoords;
    b2Vec2 lastmousecoords;
    bool isholdingfish;
    const int BOX_SIZE = 175;
    const int CONVEYOR_BELT_Y = 434;
    QRect CONVEYOR_BELT_AREA = QRect(0, 400, 1000, 250);

signals:
    void worldUpdated();
    void worldInit();
    void resetComponent();
    void correctFish();
    void wrongFish();

public slots:
    void updateWorld();
    void beginWorldStep();
    void togglePause(bool paused);
    void reset();
    void drop();
    void endGame();
    ///
    /// \brief spawnFish Spawns fish with random y
    /// coordinates on the conveyor belt. Also checks
    /// if the conveyor belt needs to speed up.
    ///
    void spawnFish ();
    void checkInvalidFish();

private:
    ///
    /// \brief INITIAL_CONVEYOR_SPEED Controls how fast the conveyor
    /// moves at the beginning
    ///
    const float INITIAL_CONVEYOR_SPEED = 300;
    ///
    /// \brief INITIAL_FISH_GENERATION_FREQUENCY How long in ms before
    /// another fish spawns to begin with
    ///
    const float INITIAL_FISH_GENERATION_FREQUENCY = 5000;
    ///
    /// \brief SPEEDUP_FREQUENCY
    ///
    const float SPEEDUP_FREQUENCY = 15000;
    ///
    /// \brief SPEEDUP_AMOUNT A ratio for control the amount the
    /// fishGenerationFrequency decreases and how much the
    /// conveyor belt increases. 1.05 indicates a 5% speedup
    ///
    const float SPEEDUP_AMOUNT = 1.05;

    void spawnBucket(int x, int y, Species species);
    bool heldFishBucketOverlap (b2Body* bucketBody);
    float conveyorSpeed;
    float fishGenerationFrequency;
    Species generateRandomSpecies();
    b2World* world;
    QTimer timer;
    QTimer fishSpawnTimer;
    QElapsedTimer timeSinceLastSpawn;
    bool paused;
    void deleteFish(b2Body* fish);
    ///
    /// \brief speedup A method called when the conveyor belt speeds up
    ///
    void speedup ();
};

#endif // GAMEMODEL_H
