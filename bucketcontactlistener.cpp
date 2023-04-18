#include "bucketcontactlistener.h"
#include "Box2D/Box2D.h"

BucketContactListener::BucketContactListener()
{

}

void BucketContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* bucket;
    b2Fixture* fish;

    bool sensorA = contact->GetFixtureA()->IsSensor();
    bool sensorB = contact->GetFixtureB()->IsSensor();


    if (sensorA && !sensorB)
    {
        bucket = contact->GetFixtureA();
        fish   = contact->GetFixtureB();
    }
    else if (sensorB && !sensorA)
    {
        fish   = contact->GetFixtureA();
        bucket = contact->GetFixtureB();
    }
    else
        return;



}


void BucketContactListener::EndContact(b2Contact* contact)
{

}
