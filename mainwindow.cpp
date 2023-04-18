#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToGame()
{
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(true);
    ui->gameOverScreen->setVisible(false);
    ui->gameScene->setFocusPolicy(Qt::StrongFocus);
    ui->gameScene->setFocus();
    emit startGame();
}

void MainWindow::switchToGameOver()
{
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(true);
}

void MainWindow::switchToHome() {
    ui->startButton->setVisible(true);
    ui->fishEduction->setVisible(true);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(false);
}
