#include "chumeducation.h"
#include "ui_chumeducation.h"
#include <QHoverEvent>

ChumEducation::ChumEducation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChumEducation) {
    ui->setupUi(this);
    fishes.push_back({ui->oceanPhase, ui->oceanEducation});
    fishes.push_back({ui->spawningPhase, ui->spawningEducation});

    connect(ui->backButton,
            &QPushButton::clicked,
            this,
            &ChumEducation::goBack);

    this->setAttribute(Qt::WA_Hover, true);

    for (auto fish : fishes)
    {
        displayNotHoverFish(fish);
    }

}

ChumEducation::~ChumEducation() {
    delete ui;
}

bool ChumEducation::event(QEvent* event) {
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

void ChumEducation::hoverEnter(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChumEducation::hoverMove(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChumEducation::hoverLeave(QHoverEvent *event) {
    QPoint point = event->position().toPoint();

    hoverOverFish(point.x(), point.y());
}

void ChumEducation::hoverOverFish(int x, int y) {
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

void ChumEducation::displayHoverFish(std::pair<QLabel *, QLabel *> fishInfo)  {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(true);
    ui->instructionLabel->setVisible(false);
}

void ChumEducation::displayNotHoverFish(std::pair<QLabel *, QLabel *> fishInfo) {
    fishInfo.first->setVisible(true);
    fishInfo.second->setVisible(false);
}
