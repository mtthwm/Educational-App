#ifndef FISHEDUCATION_H
#define FISHEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

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
    void hoverOverFish(int x, int y, std::tuple< QLabel* , QLabel*, QLabel*>);
    void displayHoverFish(std::tuple< QLabel* , QLabel*, QLabel*>);
    void displayNotHoverFish(std::tuple< QLabel* , QLabel*, QLabel*>);
    vector<std::tuple< QLabel* , QLabel*, QLabel*>> fishes;
};

#endif // FISHEDUCATION_H
