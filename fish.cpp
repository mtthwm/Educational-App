#include "fish.h"
#include <QRandomGenerator>

Fish& Fish::operator =(Fish other) {
    std::swap(variant, other.variant);
    std::swap(species, other.species);
    return *this;
}

Fish::Fish(QObject* parent, Species species) : QObject{parent}, species(species),
    variant(QRandomGenerator::global()->bounded(1, 6)) {;}

bool Fish::isOutOfBounds(float x, float y, float boundX, float boundY) {
    float posX = x + imageWidth/2;
    float posY = y + imageHeight/2;
    return posX > boundX + imageWidth/2 || posY < 0 - imageHeight/2;
}

Fish::Fish(const Fish& other) : QObject() {
    this->variant = other.variant;
    this->species = other.species;
    imageHeight = other.imageHeight;
    imageWidth = other.imageWidth;
}

