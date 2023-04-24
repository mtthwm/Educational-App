#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include "bucket.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>
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
    void spawnFish ();
    void checkInvalidFish();

private:
    void spawnBucket(int x, int y, Species species);
    bool heldFishBucketOverlap (b2Body* bucketBody);
    Species generateRandomSpecies();
    b2World* world;
    QTimer timer;
    QTimer fishSpawnTimer;
    bool paused;
    void deleteFish(b2Body* fish);
};

#endif // GAMEMODEL_H
