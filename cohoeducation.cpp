#include "cohoeducation.h"
#include "ui_cohoeducation.h"
#include <QHoverEvent>

CohoEducation::CohoEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CohoEducation)
{
    ui->setupUi(this);
    fishes.push_back({ui->oceanPhase, ui->oceanEducation});
    fishes.push_back({ui->spawningPhase, ui->spawningEducation});

    connect(ui->backButton,
            &QPushButton::clicked,
            this,
            &CohoEducation::backButtonClicked);

    this->setAttribute(Qt::WA_Hover, true);

    for (auto fish : fishes)
    {
        displayNotHoverFish(fish);
    }
}

CohoEducation::~CohoEducation()
{
    delete ui;
}

bool CohoEducation::event(QEvent* event) {
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

void CohoEducation::hoverEnter(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void CohoEducation::hoverMove(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void CohoEducation::hoverLeave(QHoverEvent *event)
{
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void CohoEducation::hoverOverFish(int x, int y)
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

void CohoEducation::displayHoverFish(std::pair<QLabel *, QLabel *> fishInfo)  {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(true);
    ui->instructionLabel->setVisible(false);
}

void CohoEducation::displayNotHoverFish(std::pair<QLabel *, QLabel *> fishInfo) {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(false);
}


void CohoEducation::backButtonClicked() {
    emit goBack();
}

