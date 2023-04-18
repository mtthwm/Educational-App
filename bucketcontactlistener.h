#ifndef BUCKETCONTACTLISTENER_H
#define BUCKETCONTACTLISTENER_H

#include "Box2D/Box2D.h"


class BucketContactListener : public b2ContactListener
{
public:
    BucketContactListener();

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // BUCKETCONTACTLISTENER_H
