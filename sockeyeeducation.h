#ifndef SOCKEYEEDUCATION_H
#define SOCKEYEEDUCATION_H

#include <QWidget>

namespace Ui {
class SockeyeEducation;
}

class SockeyeEducation : public QWidget
{
    Q_OBJECT

public:
    explicit SockeyeEducation(QWidget *parent = nullptr);
    ~SockeyeEducation();

private:
    Ui::SockeyeEducation *ui;
};

#endif // SOCKEYEEDUCATION_H
