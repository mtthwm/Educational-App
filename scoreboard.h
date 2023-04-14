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
    int score = 0;

    void addScore();
    void addScore(int amount);

private:
    Ui::ScoreBoard *ui;
};

#endif // SCOREBOARD_H
