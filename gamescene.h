#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QTimer>
#include <vector>
#include <QKeyEvent>
#include "fish.h"
#include "gamemodel.h"
#include "Box2D/Box2D.h"

using std::vector;

namespace Ui {
class GameScene;
}

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();

    ///
    /// \brief paintEvent draws the screen
    ///
    void paintEvent(QPaintEvent *);

signals:
    ///
    /// \brief gameOver notifies other components the game is over and the gameoverscreen should be displayed
    ///
    void gameOver();
    ///
    /// \brief exit notifies other components that the game is exiting and the home screen should be displayed
    ///
    void exit();
    ///
    /// \brief drop notifies the model the held fish is being dropped
    ///
    void drop();

public slots:
    ///
    /// \brief worldUpdated updates the screen when called
    ///
    void worldUpdated();
    ///
    /// \brief worldInit resets the game when called
    ///
    void worldInit();
    ///
    /// \brief mousePressEvent called by clicking the mouse, checks if a fish should be picked up
    /// \param event gives mouse coordinates
    ///
    void mousePressEvent(QMouseEvent *event);
    ///
    /// \brief mouseMoveEvent called by moving the mouse, updates lastmousecoords in GameModel
    /// \param event gives mouse coordinates
    ///
    void mouseMoveEvent(QMouseEvent *event);
    ///
    /// \brief mouseReleaseEvent called by releasing the mouse click, releases a fish if one is being held
    ///
    void mouseReleaseEvent(QMouseEvent *);
    ///
    /// \brief keyPressEvent called by pressing a key on the keyboard, displays an exit button if escape is pressed
    /// \param event gives the key pressed
    ///
    void keyPressEvent(QKeyEvent *event);
    ///
    /// \brief exitGame called by the exit button, returns to the home screen
    ///
    void exitGame();


    void showPlusOne();
    void showStrike();

private:
    Ui::GameScene *ui;
    // the GameModel holds all information about the game
    GameModel model;
    ///
    /// \brief getImage gets the image for a fish based on its species and variant
    /// \param fish
    /// \return QImage image for the fish
    ///
    QImage getImage(const Fish& fish);
    //width of the scene
    const int SCENEWIDTH = 1000;
    ///
    /// \brief SCALING_FACTOR The ratio of screen coordinates to Box2D coordinates.
    ///
    const float SCALE_FACTOR = 1000.0f;
    // stores image for fish buckets
    QImage bucketImage;
};

#endif // GAMESCENE_H
