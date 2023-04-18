#include "escapemenu.h"
#include "ui_escapemenu.h"

EscapeMenu::EscapeMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EscapeMenu)
{
    ui->setupUi(this);
}

EscapeMenu::~EscapeMenu()
{
    delete ui;
}
