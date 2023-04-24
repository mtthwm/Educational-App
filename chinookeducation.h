#ifndef CHINOOKEDUCATION_H
#define CHINOOKEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class ChinookEducation;
}

class ChinookEducation : public QWidget
{
    Q_OBJECT

public:
    explicit ChinookEducation(QWidget *parent = nullptr);
    ~ChinookEducation();

protected:
    bool event(QEvent* event);

    void hoverEnter(QHoverEvent* event);
    void hoverLeave(QHoverEvent* event);
    void hoverMove(QHoverEvent *event);

signals:
    void goBack();

private slots:
    void backButtonClicked();

private:
    Ui::ChinookEducation *ui;
    void hoverOverFish(int x, int y);
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // CHINOOKEDUCATION_H
