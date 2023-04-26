#include "pinkeducation.h"
#include "ui_pinkeducation.h"
#include <QHoverEvent>

PinkEducation::PinkEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinkEducation) {
    ui->setupUi(this);
    fishes.push_back({ui->oceanPhase, ui->oceanEducation});
    fishes.push_back({ui->spawningPhase, ui->spawningEducation});

    connect(ui->backButton,
            &QPushButton::clicked,
            this,
            &PinkEducation::goBack);

    this->setAttribute(Qt::WA_Hover, true);

    for (auto fish : fishes)
    {
        displayNotHoverFish(fish);
    }
}

PinkEducation::~PinkEducation() {
    delete ui;
}

bool PinkEducation::event(QEvent* event) {
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

void PinkEducation::hoverEnter(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void PinkEducation::hoverMove(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void PinkEducation::hoverLeave(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void PinkEducation::hoverOverFish(int x, int y) {
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

void PinkEducation::displayHoverFish(std::pair<QLabel *, QLabel *> fishInfo)  {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(true);
    ui->instructionLabel->setVisible(false);
}

void PinkEducation::displayNotHoverFish(std::pair<QLabel *, QLabel *> fishInfo) {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(false);
}
