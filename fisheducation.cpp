#include "fisheducation.h"
#include "ui_fisheducation.h"
#include <QHoverEvent>

FishEducation::FishEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FishEducation)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover, true);
}

FishEducation::~FishEducation()
{
    delete ui;
}

//void FishEducation::enterEvent(QHoverEvent*)
//{
//    ui->label->setVisible(false);
//}

//void FishEducation::leaveEvent(QHoverEvent*)
//{
//    ui->label->setVisible(true);
//}
