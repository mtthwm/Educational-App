#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include "bucket.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>
#include <QHash>
#include "bucketcontactlistener.h"

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

signals:
    void worldUpdated();
    void worldInit();
    void gameOver();
    void resetComponent();

public slots:
    void updateWorld();
    void beginWorldStep();
    void togglePause(bool paused);
    void reset();

private:
    void spawnFish ();
    void spawnBucket(int x, int y, Species species);
    Species generateRandomSpecies();
    b2World world;
    QTimer timer;
    int width;
    int height;
    bool paused;
    BucketContactListener bucketListener;

};

#endif // GAMEMODEL_H
