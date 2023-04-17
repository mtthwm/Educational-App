#include "bucket.h"

Bucket::Bucket(QObject *parent, b2Body* body, Species target)
    : QObject{parent}, body(body), targetSpecies(target) {;}

Bucket::Bucket(const Bucket& other) {
    this->targetSpecies = other.targetSpecies;
    *this->body = *(other.body);
}
