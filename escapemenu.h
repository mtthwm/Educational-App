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

public slots:
    void resumeClicked();
    void exitClicked();
signals:
    void resume();
    void exit();
private:
    Ui::EscapeMenu *ui;
};

#endif // ESCAPEMENU_H
