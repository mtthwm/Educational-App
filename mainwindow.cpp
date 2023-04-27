#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1000,670);

    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->fishEduction->setVisible(true);
    ui->startButton->setVisible(true);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);

    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToGame);
    connect(ui->gameScene,
            &GameScene::gameOver,
            this,
            &MainWindow::switchToGameOver);

    connect(ui->gameOverScreen,
            &GameOverScreen::playAgain,
            this,
            &MainWindow::switchToGame);

    connect(this,
            &MainWindow::startGame,
            ui->gameScene,
            &GameScene::worldInit);

    connect(ui->gameScene,
            &GameScene::exit,
            this,
            &MainWindow::switchToHome);

    connect(ui->gameOverScreen,
            &GameOverScreen::exit,
            this,
            &MainWindow::switchToHome);


    connect(ui->fishEduction,
            &FishEducation::goToChinook,
            this,
            &MainWindow::switchToChinook);

    connect(ui->chinookEducation,
            &ChinookEducation::goBack,
            this,
            &MainWindow::switchToHome);

    connect(ui->fishEduction,
            &FishEducation::goToSockeye,
            this,
            &MainWindow::switchToSockeye);

    connect(ui->sockeyeEducation,
            &SockeyeEducation::goBack,
            this,
            &MainWindow::switchToHome);

    connect(ui->fishEduction,
            &FishEducation::goToChum,
            this,
            &MainWindow::switchToChum);

    connect(ui->chumEducation,
            &ChumEducation::goBack,
            this,
            &MainWindow::switchToHome);

    connect(ui->fishEduction,
            &FishEducation::goToCoho,
            this,
            &MainWindow::switchToCoho);

    connect(ui->cohoEducation,
            &CohoEducation::goBack,
            this,
            &MainWindow::switchToHome);

    connect(ui->fishEduction,
            &FishEducation::goToPink,
            this,
            &MainWindow::switchToPink);

    connect(ui->pinkEducation,
            &PinkEducation::goBack,
            this,
            &MainWindow::switchToHome);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::switchToGame() {
    ui->startButton->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(true);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->gameScene->setFocusPolicy(Qt::StrongFocus);
    ui->gameScene->setFocus();
    emit startGame();
}

void MainWindow::switchToGameOver() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(true);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
}

void MainWindow::switchToHome() {
    ui->fishEduction->setVisible(true);
    ui->startButton->setVisible(true);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
}

void MainWindow::switchToChinook() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->chinookEducation->setVisible(true);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
}

void MainWindow::switchToSockeye() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(true);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
}

void MainWindow::switchToChum() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(true);
}

void MainWindow::switchToCoho() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(true);
    ui->pinkEducation->setVisible(false);
    ui->chumEducation->setVisible(false);
}

void MainWindow::switchToPink() {
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
    ui->chinookEducation->setVisible(false);
    ui->sockeyeEducation->setVisible(false);
    ui->cohoEducation->setVisible(false);
    ui->pinkEducation->setVisible(true);
    ui->chumEducation->setVisible(false);
}
