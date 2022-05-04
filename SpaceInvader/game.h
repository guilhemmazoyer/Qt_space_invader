#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game(QWidget * parent=NULL);

    QGraphicsScene * scene;
    int sceneWidth;
    int sceneHeight;

public slots:
    void fullscreen();
    void display();
    void displaySettings();
    void lowSettings();
    void mediumSettings();
    void highSettings();
};

#endif // GAME_H
