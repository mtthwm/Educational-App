#ifndef FISH_H
#define FISH_H

#include <QObject>
#include "Species.h"

class Fish : public QObject
{

    Q_OBJECT

public:
    explicit Fish(QObject *parent = nullptr, QImage* image = nullptr, Species species = Species::None);
    Species getSpecies() const;
    QImage getImage() const;

signals:

private:
    Species species;
    QImage *fishImage;

};

#endif // FISH_H
