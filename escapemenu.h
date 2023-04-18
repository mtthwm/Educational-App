#ifndef ESCAPEMENU_H
#define ESCAPEMENU_H

#include <QDialog>

namespace Ui {
class EscapeMenu;
}

class EscapeMenu : public QWidget
{
    Q_OBJECT

public:
    explicit EscapeMenu(QWidget *parent = nullptr);
    ~EscapeMenu();
    Ui::EscapeMenu *ui;


private:
};

#endif // ESCAPEMENU_H
