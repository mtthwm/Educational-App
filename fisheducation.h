#ifndef FISHEDUCATION_H
#define FISHEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class FishEducation;
}

class FishEducation : public QWidget
{
    Q_OBJECT

public:
    explicit FishEducation(QWidget *parent = nullptr);
    ~FishEducation();
protected:

    ///
    /// \brief event static casts an event into a QHoverEvent and sends it to the proper handler depending on it's original type
    /// \param event an event to be sent to one of the hover handlers
    /// \return true if it was a hover event, false otherwise
    ///
    bool event(QEvent* event);
    ///
    /// \brief hoverEnter gets the position of the hover in a point and passes that information along
    /// \param event the hover event
    ///
    void hoverEnter(QHoverEvent* event);
    ///
    /// \brief hoverLeave gets the position of the hover in a point and passes that information along
    /// \param event the hover event
    ///
    void hoverLeave(QHoverEvent* event);
    ///
    /// \brief hoverMove gets the position of the hover in a point and passes that information along
    /// \param event the hover event
    ///
    void hoverMove(QHoverEvent *event);

signals:
    ///
    /// \brief goToChinook emited when the chinook fish button is clicked
    ///
    void goToChinook();
    ///
    /// \brief goToSockeye emited when the sockeye fish button is clicked
    ///
    void goToSockeye();
    ///
    /// \brief goToPink emited when the pink fish button is clicked
    ///
    void goToPink();
    ///
    /// \brief goToChum emited when the chum fish button is clicked
    ///
    void goToChum();
    ///
    /// \brief goToCoho emited when the coho fish button is clicked
    ///
    void goToCoho();

private:
    ///
    /// \brief ui
    ///
    Ui::FishEducation *ui;
    ///
    /// \brief hoverOverFish checks to see if the current position of the mouse is over any of the fish.
    /// if so, some things are displayed, otherwise, other stuff is displayed
    /// \param x x position of the hover
    /// \param y y position of the hover
    ///
    void hoverOverFish(int x, int y);
    ///
    /// \brief displayHoverFish displays the name of the fish and changes the darkness of the fish image
    ///
    void displayHoverFish(std::tuple< QLabel* , QLabel*>);
    ///
    /// \brief displayNotHoverFish displays the standard image of the fish with nothing extra
    ///
    void displayNotHoverFish(std::tuple< QLabel* , QLabel*>);
    ///
    /// \brief fishes the storage of the fish with both types of displays being before and after a user hovers
    ///
    vector<std::tuple< QLabel* , QLabel*>> fishes;

    ///
    /// \brief driveHover just to get rid of some duplicate code. This is what would go in all of the hover handlers.
    /// \param event
    ///
    void driveHover(QHoverEvent* event);
};

#endif // FISHEDUCATION_H
