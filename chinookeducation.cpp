#include "chinookeducation.h"
#include "ui_chinookeducation.h"
#include <QHoverEvent>


ChinookEducation::ChinookEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChinookEducation)
{
    ui->setupUi(this);
    fishes.push_back({ui->oceanPhase, ui->oceanEducation});
    fishes.push_back({ui->spawningPhase, ui->spawningEducation});

    for (auto fish : fishes)
    {
        displayNotHoverFish(fish);
    }
}

ChinookEducation::~ChinookEducation()
{
    delete ui;
}

bool ChinookEducation::event(QEvent* event) {
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

void ChinookEducation::hoverEnter(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChinookEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChinookEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChinookEducation::hoverOverFish(int x, int y)
{
    for (auto fish : fishes)
    {
        QLabel* fishLabel = fish.first;

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

void ChinookEducation::displayHoverFish(std::pair<QLabel *, QLabel *> fishInfo)  {
    fishInfo.first->setVisible(false);
    fishInfo.second->setVisible(true);
}

void ChinookEducation::displayNotHoverFish(std::pair<QLabel *, QLabel *> fishInfo) {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(false);
}


void ChinookEducation::on_backButton_clicked()
{
    emit goBack();
}

