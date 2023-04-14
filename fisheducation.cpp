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

    ui->cohoAfterHover->setVisible(false);
    ui->cohoBeforeHover->setVisible(true);
    ui->dialogueLabel->setVisible(false);


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
    {
            ui->cohoAfterHover->setVisible(true);
            ui->cohoBeforeHover->setVisible(false);
            ui->dialogueLabel->setVisible(true);
    }
}

void FishEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverFish(point.x(), point.y()))
    {
        ui->cohoAfterHover->setVisible(true);
        ui->cohoBeforeHover->setVisible(false);
        ui->dialogueLabel->setVisible(true);
    }
    else
    {
        ui->cohoAfterHover->setVisible(false);
        ui->cohoBeforeHover->setVisible(true);
        ui->dialogueLabel->setVisible(false);
    }

}

void FishEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverFish(point.x(), point.y()))
    {
        ui->cohoAfterHover->setVisible(true);
        ui->cohoBeforeHover->setVisible(false);
        ui->dialogueLabel->setVisible(true);
    }
    else
    {
        ui->cohoAfterHover->setVisible(false);
        ui->cohoBeforeHover->setVisible(true);
        ui->dialogueLabel->setVisible(false);
    }
}

bool FishEducation::hoverOverFish(int x, int y)
{
    int minX      = ui->cohoBeforeHover->x();
    int minY      = ui->cohoBeforeHover->y();
    int maxX      = minX + ui->cohoBeforeHover->width();
    int maxY      = minY + ui->cohoBeforeHover->height();

    if (x > minX && y > minY
            && x < maxX
            && y < maxY)
        return true;
    return false;
}
