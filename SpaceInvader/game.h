#ifndef GAME_H
#define GAME_H

#include <string>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QSoundEffect>
#include <QSlider>
#include <QBoxLayout>

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE
class SlidersGroup;

class Game: public QGraphicsView{
    Q_OBJECT

private:
    QSlider *slider;

public:
    Game(QWidget *parent = nullptr);

    QGraphicsScene * scene;
    int sceneWidth;
    int sceneHeight;

    QSoundEffect jukebox;
    QSoundEffect interfaceMusic;
    int generalVolume;
    int musicVolume;
    int interfaceVolume;

    bool fullscreenState;

    void changeBackground(QString path);
    float getMusicVolume();
    float getInterfaceVolume();
    void setsound(QString path, int type, int loopCount = 0);

public slots:
    void fullscreen();
    void display();
    void displayMenu();
    void displaySettings();
    void launchGame();
};

#endif // GAME_H
