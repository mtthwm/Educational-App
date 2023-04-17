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


    fishes.push_back({ui->cohoBeforeHover, ui->cohoAfterHover, ui->cohoDialogueLabel});

    fishes.push_back({ui->kingBeforeHover, ui->kingAfterHover, ui->kingDialogueLabel});

    fishes.push_back({ui->sockeyeBeforeHover, ui->sockeyeAfterHover, ui->sockeyeDialogueLabel});

    fishes.push_back({ui->pinkBeforeHover, ui->pinkAfterHover, ui->pinkDialogueLabel});

    fishes.push_back({ui->chumBeforeHover, ui->chumAfterHover, ui->chumDialogueLabel});

    for (auto fish : fishes)
    {
        displayNotHoverFish(fish);
    }

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

    hoverOverFish(point.x(), point.y());
}

void FishEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void FishEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void FishEducation::hoverOverFish(int x, int y)
{
    for (auto fish : fishes)
    {
        QLabel* fishLabel = std::get<0>(fish);

        int minX      = fishLabel->x();
        int minY      = fishLabel->y();
        int maxX      = minX + fishLabel->width();
        int maxY      = minY + fishLabel->height();

        bool xInBounds = x > minX && x < maxX;
        bool yInBounds = y > minY && y < maxY;

        if (xInBounds && yInBounds)
            displayHoverFish(fish);
        else
            displayNotHoverFish(fish);
    }
}

void FishEducation::displayHoverFish(std::tuple< QLabel* , QLabel*, QLabel*> fishInfo)
{
    //before hover
    std::get<0>(fishInfo)->setVisible(false);
    //after hover
    std::get<1>(fishInfo)->setVisible(true);
    //dialog
    std::get<2>(fishInfo)->setVisible(true);
}

void FishEducation::displayNotHoverFish(std::tuple< QLabel* , QLabel*, QLabel*> fishInfo)
{
    //before hover
    std::get<0>(fishInfo)->setVisible(true);
    //after hover
    std::get<1>(fishInfo)->setVisible(false);
    //dialog
    std::get<2>(fishInfo)->setVisible(false);
}
