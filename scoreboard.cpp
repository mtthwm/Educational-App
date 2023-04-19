#include "scoreboard.h"
#include "ui_scoreboard.h"

#include <qstring.h>

ScoreBoard::ScoreBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard),
    score{0}
{
    ui->setupUi(this);

    numStrikes = 3;

    updateUI();
}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::addScore() {
    score += 1;
    updateUI();
}

void ScoreBoard::reset () {
    score = 0;
    updateUI();
}

void ScoreBoard::updateUI() {
    ui->scoreLabel->setText(QString::number(score));
    emit scoreUpdated(score);
}

void ScoreBoard::addStrike() {
    QString numStrikesString = "";
    numStrikes--;
    for (int i = 0; i < numStrikes; i++)
        {
            numStrikesString += "I";
        }

    ui->numStrikes->setText(numStrikesString);

    if (numStrikes == 0)
    {
        emit gameOver();
        return;
    }
}
