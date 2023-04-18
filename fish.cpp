#include "fish.h"
#include <QImage>

Fish::Fish(QObject *parent, int variant, Species species, b2Body* body)
    : QObject{parent}, species(species), body(body), variant(variant)
{

}

Fish::~Fish() {
    body->GetWorld()->DestroyBody(body);
}

Fish& Fish::operator =(Fish other) {
    std::swap(variant, other.variant);
    std::swap(species, other.species);
    std::swap(body, other.body);
    return *this;
}

Fish::Fish(QObject* parent, Species species) : QObject{parent}, species(species),
    body(nullptr), variant(0)
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

Fish::Fish(const Fish& other) {
    *this->body = *(other.body);
    this->variant = other.variant;
    this->species = other.species;
}
