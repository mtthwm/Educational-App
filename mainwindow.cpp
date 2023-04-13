#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gameScene->setVisible(false);

    connect(ui->startButton,
            &QPushButton::clicked,
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
}

