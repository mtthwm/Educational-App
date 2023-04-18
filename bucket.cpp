#include "bucket.h"

Bucket::Bucket(QObject *parent, b2Body* body, Species target)
    : QObject{parent}, body(body), targetSpecies(target) {;}

Bucket::Bucket(const Bucket& other) {
    this->targetSpecies = other.targetSpecies;
    *this->body = *(other.body);
}

Bucket::~Bucket() {
    body->GetWorld()->DestroyBody(body);
}

Bucket& Bucket::operator= (Bucket other) {
    std::swap(body, other.body);
    targetSpecies = other.targetSpecies;
    return *this;
}
