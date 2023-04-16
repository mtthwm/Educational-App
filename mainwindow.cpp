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
}

void MainWindow::switchToGameOver()
{
    ui->startButton->setVisible(false);
    ui->fishEduction->setVisible(false);
    ui->gameScene->setVisible(false);
    ui->gameOverScreen->setVisible(true);
}
