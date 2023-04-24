#ifndef WALL_H
#define WALL_H

#include "Box2D/Box2D.h"
#include <QPoint>
class Wall
{

public:
    Wall();
    Wall(QPoint p1, QPoint p2, int width);
    Wall(const Wall& other);
    Wall& operator=(Wall other);
    QPoint p1, p2;
    int length;
    int width;
    bool isSensor;
    QPoint getTopLeft();
    bool isVertical();
signals:

private:
    int calculateDistance();

};

#endif // WALL_H
