#include "scoreboard.h"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreBoard),
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
    addScore(1);
}

void ScoreBoard::addScore(int amount) {
    score += amount;
    updateUI();
}

void ScoreBoard::updateUI() {
    ui->scoreLabel->setText(QString::number(score));
}
