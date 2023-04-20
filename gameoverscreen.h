#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>

namespace Ui {
class GameOverScreen;
}

class GameOverScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);
    ~GameOverScreen();

signals:
    void playAgain();
    void exit();

private:
    Ui::GameOverScreen *ui;
};

#endif // GAMEOVERSCREEN_H
