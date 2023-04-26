/*
Team Null - A8 Educational App Assignment
Last Modified: Matthew Morales - 4/17/2023
*/

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>

///
/// This class deals with graphics of the scoreboard as well as keeping track of whether the game is over or not.
/// Score and strikes are incremented based off of actions from the user and signals from the game model
///

namespace Ui {
class ScoreBoard;
}

class ScoreBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard();

public slots:
    ///
    /// \brief addScore Adds one to the score
    ///
    void addScore ();
    ///
    /// \brief addStrike adds a strike if there is zero or 1 strikes. If there is 2 strikes, the game ends
    ///
    void addStrike();
    ///
    /// \brief reset Resets the score to zero
    ///
    void reset ();

signals:
    ///
    /// \brief scoreUpdated Emitted whenever the score is updated
    /// \param newScore The new score
    ///
    void scoreUpdated (int newScore);

    ///
    /// \brief gameOver
    ///
    void gameOver();

private:
    Ui::ScoreBoard *ui;

    ///
    /// \brief MAX_STRIKES How many strikes the player can get
    /// before getting fired.
    ///
    const int MAX_VISIBLE_STRIKES = 2;

    int numStrikes;

    ///
    /// \brief score The current score
    ///
    int score;

    ///
    /// \brief updateUI Updates the UI to reflect the current score
    ///
    void updateUI ();
};

#endif // SCOREBOARD_H
