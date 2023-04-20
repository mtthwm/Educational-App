#include "escapemenu.h"
#include "ui_escapemenu.h"

EscapeMenu::EscapeMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EscapeMenu)
{
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &EscapeMenu::exitClicked);
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
