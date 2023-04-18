#include "escapemenu.h"
#include "ui_escapemenu.h"

EscapeMenu::EscapeMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EscapeMenu)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &EscapeMenu::resumeClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &EscapeMenu::exitClicked);
}

EscapeMenu::~EscapeMenu()
{
    delete ui;
}

void EscapeMenu::exitClicked() {
    emit exit();
}

void EscapeMenu::resumeClicked() {
    emit resume();
}
