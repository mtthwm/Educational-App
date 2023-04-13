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

private:
    Ui::FishEducation *ui;
};

#endif // FISHEDUCATION_H
