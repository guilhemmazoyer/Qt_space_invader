#include <QApplication>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    //game->setWindowState(Qt::WindowFullScreen);
    //game->showFullScreen();
    game->show();
    game->display();

    return a.exec();
}
