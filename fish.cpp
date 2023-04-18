#include "fish.h"
#include <QImage>


Fish::~Fish() {
}

Fish& Fish::operator =(Fish other) {
    std::swap(variant, other.variant);
    std::swap(species, other.species);
    //std::swap(body, other.body);
    return *this;
}

Fish::Fish(QObject* parent, Species species) : QObject{parent}, species(species),
    variant(0)
{
    switch (this->species) {
        case Species::Coho:
            break;
        case Species::Sockeye:
            break;
        case Species::Chinook:
            break;
        case Species::Pink:
            break;
        case Species::Chum:
            break;
        case Species::None:
            break;
    }
}

Fish::Fish(const Fish& other) : QObject() {
    //this->body = other.body;
    this->variant = other.variant;
    this->species = other.species;
    imageHeight = other.imageHeight;
    imageWidth = other.imageWidth;
}

