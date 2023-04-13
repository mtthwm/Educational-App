#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QTimer>
#include "Box2D/Box2D.h"

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

    b2World world;
    b2Body* fishBody;
    QTimer timer;
};

#endif // GAMESCENE_H
