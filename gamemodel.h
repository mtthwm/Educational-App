#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include "bucket.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>
#include <QHash>

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
    const int BOX_SIZE = 200;

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

private:
    void spawnFish ();
    void spawnBucket(int x, int y, Species species);
    bool heldFishBucketOverlap (b2Body* bucketBody);
    Species generateRandomSpecies();
    b2World* world;
    QTimer timer;
    int width;
    int height;
    bool paused;
};

#endif // GAMEMODEL_H
