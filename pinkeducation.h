#ifndef PINKEDUCATION_H
#define PINKEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;

namespace Ui {
class PinkEducation;
}

class PinkEducation : public QWidget
{
    Q_OBJECT

public:
    explicit PinkEducation(QWidget *parent = nullptr);
    ~PinkEducation();

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
    Ui::PinkEducation *ui;
    void hoverOverFish(int x, int y);
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // PINKEDUCATION_H
