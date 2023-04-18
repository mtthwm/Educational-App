#ifndef BUCKET_H
#define BUCKET_H

#include <QObject>
#include "Species.h"
#include "Box2D/Box2D.h"

class Bucket : public QObject
{
    Q_OBJECT
public:
    explicit Bucket(QObject *parent = nullptr, b2Body* = nullptr, Species target = Species::None);
    Bucket(const Bucket&);
    ~Bucket();
    Bucket& operator= (Bucket);
    //b2Body* body;
    Species targetSpecies;
signals:

};

#endif // BUCKET_H
