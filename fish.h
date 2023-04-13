#ifndef FISH_H
#define FISH_H

#include <QObject>
#include "Species.h"
#include "Box2D/Box2D.h"

class Fish : public QObject
{

    Q_OBJECT

public:
    explicit Fish(QObject *parent = nullptr, QImage* image = nullptr, Species species = Species::None, b2Body *body = nullptr);
    Species species;
    QImage *fishImage;
    b2Body *body;

signals:

};

#endif // FISH_H
