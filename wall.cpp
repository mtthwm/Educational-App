#include "wall.h"

///
/// \brief Wall::Wall The wall class has some special rules that must be
///  followed in order for it to work properly.
///  1. p1 must always come before p2, i.e. p1.x < p2.x or p1.y > p2.y if the wall is vertical.
///  2. the points go at the very end of the walls i.e. there is no buffer wall in front of each point.
/// \param p1 The first endpoint of the wall.
/// \param p2 The second endpoint of the wall.
/// \param width The width of the wall.
///
Wall::Wall(QPoint p1, QPoint p2, int width) : p1(p1), p2(p2), width(width)
{
    length = calculateDistance();
}

Wall::Wall() {;}

int Wall::calculateDistance() {
    return (int)(sqrt((pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2))));
}

Wall::Wall(const Wall& other) {
    this->p1 = other.p1;
    this->p2 = other.p2;
    this->isSensor = other.isSensor;
    this->length = other.length;
    this->width = other.width;
}

Wall& Wall::operator =(Wall other) {
    std::swap(p1, other.p1);
    std::swap(p2, other.p2);
    std::swap(length, other.length);
    std::swap(width, other.width);
    std::swap(isSensor, other.isSensor);
    return *this;
}

QPoint Wall::getTopLeft() {
    if (isVertical()) {
        QPoint topLeft(p1.x() + width/2, p1.y());
        return topLeft;
    }
    QPoint topLeft(p1.x(), p1.y() + width/2);
    return topLeft;
}

bool Wall::isVertical() {
    return p1.y() > p2.y();
}
