#ifndef FISH_H
#define FISH_H

#include <QObject>
#include "Species.h"
#include "Box2D/Box2D.h"

class Fish : public QObject
{

    Q_OBJECT

public:
    explicit Fish(QObject* parent = nullptr, Species species = Species::None);
    ///
    /// \brief Fish Copy constructor.
    /// \param other The fish to copy.
    ///
    Fish(const Fish& other);
    ///
    /// \brief species The species of this fish.
    ///
    Species species;
    ///
    /// \brief variant The number corresponding to the image that
    /// will represent this fish.
    ///
    int variant;
    ///
    /// \brief imageWidth The width of the image that will represent
    /// this fish.
    /// \brief imageHeight The height of the image that will represent
    /// this fish.
    ///
    int imageWidth, imageHeight;
    ///
    /// \brief operator =
    /// \param other The fish to copy.
    /// \return
    ///
    Fish& operator=(Fish other);
    ///
    /// \brief isOutOfBounds Tells whether this fish is outside of the given x,y bounds.
    /// \param x The x position of this fish (from a b2Body)
    /// \param y The y position of this fish (from a b2Body)
    /// \param boundX The x-bound of the area to check.
    /// \param boundY The y-bound of the area to check.
    /// \return True if it's out of bounds, false otherwise.
    ///
    bool isOutOfBounds(int x, int y, int boundX, int boundY);
signals:
    // None.
private:
};

#endif // FISH_H
