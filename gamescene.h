#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QTimer>
#include <vector>
#include <QKeyEvent>
#include "fish.h"
#include "bucket.h"
#include "gamemodel.h"
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

signals:
    void gameOver();
    void beginWorldStep();
    void exit();
    void drop();

public slots:
    void worldUpdated();
    void worldInit();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void showEndGameScreen();

private:
    Ui::GameScene *ui;

    void updateWorld ();
    void spawnFish ();
    GameModel model;
    QImage fishImage;
    QImage bucketImage;
    QImage getImage(const Fish& fish);
};

#endif // GAMESCENE_H
