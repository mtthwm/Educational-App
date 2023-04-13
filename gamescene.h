#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QTimer>
#include <vector>

#include "Box2D/Box2D.h"

using std::vector;

namespace Ui {
class GameScene;
}

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();

    void paintEvent(QPaintEvent *);

private:
    Ui::GameScene *ui;

    void updateWorld ();
    void spawnFish ();

    b2World world;
    vector<b2Body*> fishBodies;
    QTimer timer;
    QImage fishImage;
};

#endif // GAMESCENE_H
