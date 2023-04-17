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
    /// \brief addScore Adds a specific amount to the score
    /// \param amount The amount to add
    ///
    void addScore (int amount);
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

private:
    Ui::ScoreBoard *ui;

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
