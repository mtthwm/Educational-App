#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QHash>
#include <QRect>

using std::vector;

///
/// \brief The GameModel class deals with the core logic of the game. All physics and game play logic are in this class.
///

class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);
    ///
    /// \brief buckets A map of each bucket's b2Body to the species of fish it accepts.
    ///
    QHash<b2Body*, Species> buckets;
    ///
    /// \brief fishes A map of each fishs' b2Body to the Fish object itself.
    ///
    QHash<b2Body*, Fish> fishes;
    ///
    /// \brief worldInitialized A marker as to if the b2World and game world is ready for use.
    ///
    bool worldInitialized;
    ///
    /// \brief heldFish The b2Body of the currently held fish.
    ///
    b2Body* heldFish;
    ///
    /// \brief heldfishcoords The coordinates the fish is being held at relative to the fish.
    ///
    b2Vec2 heldfishcoords;
    ///
    /// \brief lastmousecoords The coordinates of the mouse's last position.
    ///
    b2Vec2 lastmousecoords;
    ///
    /// \brief isholdingfish true if a fish is currently being held, false otherwise.
    ///
    bool isholdingfish;
    ///
    /// \brief BOX_SIZE
    ///
    const float BOX_SIZE = 0.175f;
    ///
    /// \brief CONVEYOR_BELT_AREA
    ///
    QRectF CONVEYOR_BELT_AREA = QRectF(-0.25f, 0.367f, 1.5f, 0.245f);
    ///
    /// \brief conveyorPosition
    ///
    float conveyorPosition;
    ///
    /// \brief CONVEYOR_DISTANCE
    ///
    const float CONVEYOR_DISTANCE = 0.089f;

signals:
    ///
    /// \brief worldUpdated Emitted when the world has updated and components must update.
    ///
    void worldUpdated();
    ///
    /// \brief worldInit Emitted when the world has finished being prepared and is ready for use,
    ///
    void worldInit();
    ///
    /// \brief resetComponent Emitted when specific components such as the Scoreboard need to reset.
    ///
    void resetComponent();
    ///
    /// \brief correctFish Emitted when a fish is put into the correct bucket.
    ///
    void correctFish();
    ///
    /// \brief wrongFish Emitted when a fish is put into the wrong bucket, or when a fish goes out of bounds.
    ///
    void wrongFish();

public slots:
    ///
    /// \brief updateWorld Updates the b2World.
    ///
    void updateWorld();
    ///
    /// \brief beginWorldStep Starts the b2World updating process.
    ///
    void beginWorldStep();
    ///
    /// \brief togglePause Pauses or unpauses the game.
    /// \param paused True if pausing, false otherwise.
    ///
    void togglePause(bool paused);
    ///
    /// \brief reset Resets the game.
    ///
    void reset();
    ///
    /// \brief drop Drops the currently held fish.
    ///
    void drop();
    ///
    /// \brief endGame Ends the game.
    ///
    void endGame();
    ///
    /// \brief spawnFish Spawns fish with random y
    /// coordinates on the conveyor belt. Also checks
    /// if the conveyor belt needs to speed up.
    ///
    void spawnFish ();
    ///
    /// \brief checkInvalidFish Checks each fish in play if their positions are valid.
    ///
    void checkInvalidFish();

private:
    ///
    /// \brief INITIAL_CONVEYOR_SPEED Controls how fast the conveyor
    /// moves at the beginning
    ///
    const float INITIAL_CONVEYOR_SPEED = 0.2000f;
    ///
    /// \brief INITIAL_FISH_GENERATION_FREQUENCY How long in ms before
    /// another fish spawns to begin with
    ///
    const float INITIAL_FISH_GENERATION_FREQUENCY = 4000;
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
    ///
    /// \brief conveyorSpeed
    ///
    float conveyorSpeed;
    ///
    /// \brief spawnBucket Spawns a bucket at the specified x, y coordinate.
    /// \param x The x-location to spawn the bucket.
    /// \param y The y-location to spawn the bucket.
    /// \param species The species the bucket will accept.
    ///
    void spawnBucket(float x, float y, Species species);
    ///
    /// \brief spawnWalls
    ///
    void spawnWalls();
    ///
    /// \brief heldFishBucketOverlap
    /// \param bucketBody
    /// \return
    ///
    bool heldFishBucketOverlap (b2Body* bucketBody);
    ///
    /// \brief fishGenerationFrequency
    ///
    float fishGenerationFrequency;
    ///
    /// \brief generateRandomSpecies Generates a random fish species. See Species.h.
    /// \return The species that was generated.
    ///
    Species generateRandomSpecies();
    ///
    /// \brief world The physics world used in the game.
    ///
    b2World* world;
    ///
    /// \brief timer This timer is responsible for updating the b2World and
    /// checking for invalid fish.
    ///
    QTimer timer;
    ///
    /// \brief fishSpawnTimer
    ///
    QTimer fishSpawnTimer;
    ///
    /// \brief timeSinceLastSpawn
    ///
    QElapsedTimer timeSinceLastSpawn;
    ///
    /// \brief paused True if the game is paused, false otherwise.
    ///
    bool paused;
    ///
    /// \brief deleteFishAndBody
    /// \param fish
    ///
    void deleteFishAndBody(b2Body* fish);
    ///
    /// \brief speedup A method called when the conveyor belt speeds up
    ///
    void speedup ();

};

#endif // GAMEMODEL_H
