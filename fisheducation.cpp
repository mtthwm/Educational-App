#include "fisheducation.h"
#include "ui_fisheducation.h"

FishEducation::FishEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FishEducation)
{
    ui->setupUi(this);
}

FishEducation::~FishEducation()
{
    delete ui;
}
