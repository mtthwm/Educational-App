#include "fisheducation.h"
#include "ui_fisheducation.h"
#include <QHoverEvent>

#include <iostream>
using std::cout;
using std::endl;

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

void FishEducation::hoverEnter(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();
    cout<<point.x()<< " and Y: " << point.y() << endl;
}

//void FishEducation::enterEvent(QHoverEvent*)
//{
//    ui->label->setVisible(false);
//}

//void FishEducation::leaveEvent(QHoverEvent*)
//{
//    ui->label->setVisible(true);
//}
