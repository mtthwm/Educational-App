#ifndef COHOEDUCATION_H
#define COHOEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;


namespace Ui {
class CohoEducation;
}

class CohoEducation : public QWidget
{
    Q_OBJECT

public:
    explicit CohoEducation(QWidget *parent = nullptr);
    ~CohoEducation();

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
    Ui::CohoEducation *ui;
    void hoverOverFish(int x, int y);
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // COHOEDUCATION_H
