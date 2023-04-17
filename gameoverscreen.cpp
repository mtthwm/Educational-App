#include "gameoverscreen.h"
#include "ui_gameoverscreen.h"

GameOverScreen::GameOverScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOverScreen) {
    ui->setupUi(this);
    connect(ui->playAgainButton,
            &QPushButton::clicked,
            this,
            &GameOverScreen::playAgain);
}

GameOverScreen::~GameOverScreen() {
    delete ui;
}
