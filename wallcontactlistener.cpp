#include "wallcontactlistener.h"
#include "fish.h"
#include "wall.h"
#include <QDebug>

void WallContactListener::BeginContact(b2Contact *contact) {
   qDebug() << "Here";
}

void WallContactListener::EndContact(b2Contact *contact) {

}
