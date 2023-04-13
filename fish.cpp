#include "fish.h"

Fish::Fish(QObject *parent, QImage *image, Species species)
    : QObject{parent}, species(species), fishImage(image)
{

}
