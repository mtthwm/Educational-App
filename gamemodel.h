#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "fish.h"
#include <vector>
#include "Box2D/Box2D.h"
#include <QTimer>

using std::vector;


class GameModel : public QObject
{
    Q_OBJECT
public:
    explicit GameModel(QObject *parent = nullptr);
    void setWidth(int width);
    void setHeight(int height);

signals:
    void worldUpdated(vector<Fish>);

public slots:
    void updateWorld();

private:
    void spawnFish ();
    b2World world;
    vector<Fish> fish;
    QTimer timer;
    int width;
    int height;
};

#endif // GAMEMODEL_H
