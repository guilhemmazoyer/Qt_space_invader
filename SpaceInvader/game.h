#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <string>

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game(QWidget * parent=NULL);

    QGraphicsScene * scene;
    int sceneWidth;
    int sceneHeight;
    bool fullscreenState;

    void changeBackground(QString path);

public slots:
    void fullscreen();
    void display();
    void displaySettings();
};

#endif // GAME_H
