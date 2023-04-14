#include "fish.h"

Fish::Fish(QObject *parent, QImage *image, Species species, b2Body* body)
    : QObject{parent}, species(species), fishImage(image), body(body)
{

}

Fish::Fish(const Fish& other) {
    *this->body = *(other.body);
    this->fishImage = other.fishImage;
    this->species = other.species;
}
