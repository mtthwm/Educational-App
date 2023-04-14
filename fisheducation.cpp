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

bool FishEducation::event(QEvent* event)
{

    if (event->type() == QEvent::HoverEnter)
    {
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
    }
    if (event->type() == QEvent::HoverLeave)
    {
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
    }
    if (event->type() == QEvent::HoverMove)
    {
        hoverMove(static_cast<QHoverEvent*>(event));
    }

    return false;
}
void FishEducation::hoverEnter(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverFish(point.x(), point.y()))
            ui->transparencyBuffer->setStyleSheet("background-color: rgba(0, 0, 0, 100)");
}

void FishEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverFish(point.x(), point.y()))
            ui->transparencyBuffer->setStyleSheet("background-color: rgba(0, 0, 0, 100)");
    else
        ui->transparencyBuffer->setStyleSheet("background-color: rgba(255, 255, 255, 10)");

}

void FishEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (!hoverOverFish(point.x(), point.y()))
        ui->transparencyBuffer->setStyleSheet("background-color: rgba(255, 255, 255, 10)");
}

bool FishEducation::hoverOverFish(int x, int y)
{
    int minX      = ui->cohoImageLabel->x();
    int minY      = ui->cohoImageLabel->y();
    int maxX      = minX + ui->cohoImageLabel->width();
    int maxY      = minY + ui->cohoImageLabel->height();

    if (x > minX && y > minY
            && x < maxX
            && y < maxY)
        return true;
    return false;
}
