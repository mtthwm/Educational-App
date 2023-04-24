#ifndef SOCKEYEEDUCATION_H
#define SOCKEYEEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class SockeyeEducation;
}

class SockeyeEducation : public QWidget
{
    Q_OBJECT

public:
    explicit SockeyeEducation(QWidget *parent = nullptr);
    ~SockeyeEducation();

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
    Ui::SockeyeEducation *ui;
    void hoverOverFish(int x, int y);
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // SOCKEYEEDUCATION_H
