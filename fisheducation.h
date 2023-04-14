#ifndef FISHEDUCATION_H
#define FISHEDUCATION_H

#include <QWidget>

namespace Ui {
class FishEducation;
}

class FishEducation : public QWidget
{
    Q_OBJECT

public:
    explicit FishEducation(QWidget *parent = nullptr);
    ~FishEducation();
protected:

    bool event(QEvent* event);

    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    void hoverMove(QHoverEvent *event);


private:
    Ui::FishEducation *ui;
    bool hoverOverFish(int x, int y);
};

#endif // FISHEDUCATION_H
