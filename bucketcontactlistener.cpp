#include "bucketcontactlistener.h"
#include "Box2D/Box2D.h"
#include "bucket.h"
#include "fish.h"

BucketContactListener::BucketContactListener()
{

}

void BucketContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* bucketFixture;
    b2Fixture* fishFixture;

    bool sensorA = contact->GetFixtureA()->IsSensor();
    bool sensorB = contact->GetFixtureB()->IsSensor();

    if (sensorA && !sensorB)
    {
        bucketFixture = contact->GetFixtureA();
        fishFixture   = contact->GetFixtureB();
    }
    else if (sensorB && !sensorA)
    {
        fishFixture   = contact->GetFixtureA();
        bucketFixture = contact->GetFixtureB();
    }
    else
        return;

    Bucket* bucket = static_cast<Bucket*>(bucketFixture->GetBody()->GetUserData());

    Fish* fish = static_cast<Fish*>(fishFixture->GetBody()->GetUserData());

    bucket->fishDropped(*fish);
}


void BucketContactListener::EndContact(b2Contact* contact)
{

}
