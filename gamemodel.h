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
    QHash<b2Body*, Fish> fish;
    bool worldInitialized;

signals:
    void worldUpdated(QHash<b2Body*, Fish>);
    void worldInit();
    void gameOver();

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
};

#endif // GAMEMODEL_H
