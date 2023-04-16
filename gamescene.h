#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QTimer>
#include <vector>
#include "fish.h"

#include "Box2D/Box2D.h"
#include "fish.h"

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

signals:
    void gameOver();

public slots:
    void worldUpdated(vector<Fish>);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::GameScene *ui;

    void updateWorld ();
    void spawnFish ();

    b2World world;
    vector<b2Body*> fishBodies;
    b2Body* heldFish;
    b2Vec2 heldfishcoords;
    b2Vec2 lastmousecoords;
    bool isholdingfish;
    QTimer timer;
    QImage fishImage;
};

#endif // GAMESCENE_H
