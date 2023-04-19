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
    ui->scoreLabel->setText("stupid");
}
