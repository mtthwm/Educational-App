#include "sockeyeeducation.h"
#include "ui_sockeyeeducation.h"

SockeyeEducation::SockeyeEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SockeyeEducation)
{
    ui->setupUi(this);
}

SockeyeEducation::~SockeyeEducation()
{
    delete ui;
}
