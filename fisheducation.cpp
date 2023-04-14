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

//    ui->cohoAfterHover->setVisible(false);
//    ui->cohoBeforeHover->setVisible(true);
//    ui->dialogueLabel->setVisible(false);

    fishBeforeHover.insert({"coho", ui->cohoBeforeHover});
    fishBeforeHover.insert({"king", ui->kingBeforeHover});
    fishBeforeHover.insert({"sockeye", ui->sockeyeBeforeHover});
    fishBeforeHover.insert({"pink", ui->pinkBeforeHover});
    fishBeforeHover.insert({"chum", ui->chumBeforeHover});

    fishAfterHover.insert({"coho", ui->cohoAfterHover});
    fishAfterHover.insert({"king", ui->kingAfterHover});
    fishAfterHover.insert({"sockeye", ui->sockeyeAfterHover});
    fishAfterHover.insert({"pink", ui->pinkAfterHover});
    fishAfterHover.insert({"chum", ui->chumAfterHover});




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

    if (hoverOverCoho(point.x(), point.y()))
        displayHoverCoho();
    else
        displayNotHoverCoho();
}

void FishEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverCoho(point.x(), point.y()))
        displayHoverCoho();
    else
        displayNotHoverCoho();

}

void FishEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    if (hoverOverCoho(point.x(), point.y()))
        displayHoverCoho();
    else
        displayNotHoverCoho();
}

bool FishEducation::hoverOverCoho(int x, int y)
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

void FishEducation::displayHoverCoho()
{
    ui->cohoAfterHover->setVisible(true);
    ui->cohoBeforeHover->setVisible(false);
    ui->cohoDialogueLabel->setVisible(true);
}

void FishEducation::displayNotHoverCoho()
{
    ui->cohoAfterHover->setVisible(false);
    ui->cohoBeforeHover->setVisible(true);
    ui->cohoDialogueLabel->setVisible(false);
}
