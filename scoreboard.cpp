#include "scoreboard.h"
#include "ui_scoreboard.h"

#include <qstring.h>

ScoreBoard::ScoreBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard),
    numStrikes{0},
    score{0}
{
    ui->setupUi(this);

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
    numStrikes = 0;
    updateUI();
}

void ScoreBoard::updateUI() {
    ui->scoreLabel->setText(QString::number(score));

    if (numStrikes == 0) {
        ui->numStrikes->setText("0");
    } else {
        QString numStrikesString = "";
        for (int i = 0; i < numStrikes; i++)
            {
                numStrikesString += "I";
            }

        ui->numStrikes->setText(numStrikesString);
    }

    emit scoreUpdated(score);
}

void ScoreBoard::addStrike() {
    numStrikes++;

    if (numStrikes == MAX_STRIKES)
    {
        emit gameOver();
        numStrikes = 0;
    }

    updateUI();
}
