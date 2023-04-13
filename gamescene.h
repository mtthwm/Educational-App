#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
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

private:
    Ui::GameScene *ui;

    b2World world;
    b2Body fish;
};

#endif // GAMESCENE_H
