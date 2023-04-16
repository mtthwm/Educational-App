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
    void setWidth(int width);
    void setHeight(int height);

signals:
    void worldUpdated(QHash<b2Body*, Fish>);
    void worldInit(QHash<b2Body*, Bucket>);
    void gameOver();

public slots:
    void updateWorld();
    void beginWorldStep();
    void togglePause(bool paused);
    void reset();

private:
    void spawnFish ();
    void spawnBucket();
    Species generateRandomSpecies();
    b2World world;
    QHash<b2Body*, Fish> fish;
    QHash<b2Body*, Bucket> buckets;
    QTimer timer;
    int width;
    int height;
    bool paused;
};

#endif // GAMEMODEL_H
