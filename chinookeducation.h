#ifndef CHINOOKEDUCATION_H
#define CHINOOKEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class ChinookEducation;
}

class ChinookEducation : public QWidget
{
    Q_OBJECT

public:
    explicit ChinookEducation(QWidget *parent = nullptr);
    ~ChinookEducation();

protected:
    ///
    /// \brief event checks the event type, then casts to a hoverEvent and
    /// sends it to the appropriate handler
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
    /// \brief goBack emited when the back button is clicked
    ///
    void goBack();

private:
    Ui::ChinookEducation *ui;
    ///
    /// \brief hoverOverFish checks if the current mouse position is over either of the fish and adjusts
    /// the display accordingly.
    /// \param x x position of the hover
    /// \param y y position of the hover
    ///
    void hoverOverFish(int x, int y);
    ///
    /// \brief displayHoverFish displays the educational information over the fish image
    ///
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    ///
    /// \brief displayNotHoverFish only displays the fish, not the educational information
    ///
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    ///
    /// \brief fishes stores each fish with the fish image and the educational info.
    ///
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // CHINOOKEDUCATION_H
