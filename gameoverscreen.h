#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>

namespace Ui {
class GameOverScreen;
}

class GameOverScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);
    ~GameOverScreen();

signals:
    ///
    /// \brief playAgain emited when the play again button is clicekd
    ///
    void playAgain();
    ///
    /// \brief exit emited when the exit button is clicked
    ///
    void exit();

private:
    Ui::GameOverScreen *ui;
};

#endif // GAMEOVERSCREEN_H
