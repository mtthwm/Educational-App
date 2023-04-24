#ifndef CHUMEDUCATION_H
#define CHUMEDUCATION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;


namespace Ui {
class ChumEducation;
}

class ChumEducation : public QWidget
{
    Q_OBJECT

public:
    explicit ChumEducation(QWidget *parent = nullptr);
    ~ChumEducation();

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
    Ui::ChumEducation *ui;
    void hoverOverFish(int x, int y);
    void displayHoverFish(std::pair< QLabel* , QLabel*>);
    void displayNotHoverFish(std::pair< QLabel* , QLabel*>);
    vector<std::pair< QLabel* , QLabel*>> fishes;
};

#endif // CHUMEDUCATION_H
