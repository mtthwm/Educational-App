/*
Team Null - A8 Educational App Assignment
Last Modified: Matthew Morales - 4/17/2023
*/

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>

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
    /// \brief addStrike
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
    const int MAX_STRIKES = 3;

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
