#ifndef WALLCONTACTLISTENER_H
#define WALLCONTACTLISTENER_H

#include "Box2D/Box2D.h"


class WallContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

#endif // WALLCONTACTLISTENER_H
