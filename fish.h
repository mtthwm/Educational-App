#ifndef FISH_H
#define FISH_H

#include <QObject>
#include "Species.h"
#include "Box2D/Box2D.h"

class Fish : public QObject
{

    Q_OBJECT

public:
    explicit Fish(QObject *parent = nullptr, int variant = 0, Species species = Species::None, b2Body *body = nullptr);
    explicit Fish(QObject* parent = nullptr, Species species = Species::None);
    ~Fish();
    Fish(const Fish& other);
    Species species;
    int variant;
    int imageWidth, imageHeight;

    Fish& operator=(Fish other);
signals:

private:
};

#endif // FISH_H
