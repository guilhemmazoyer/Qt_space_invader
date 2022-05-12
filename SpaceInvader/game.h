#ifndef GAME_H
#define GAME_H

#include "enemy.h"
#include "missile.h"
#include "player.h"
#include "score.h"
#include "health.h"
#include "explosion.h"
#include "button.h"

#include <string>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QSoundEffect>
#include <QSlider>
#include <QBoxLayout>

class Game: public QGraphicsView{
    Q_OBJECT
    QSlider *slider;

public:
    Game();

    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    Enemy * enemy;
    Explosion * explosion;
    int sceneWidth;
    int sceneHeight;
    float spaceshipWidthOffset;
    int difficulty;

    bool fullscreenState;
    bool isPauseMenuClosed;
    bool isUnlimited;
    void changeBackground(QString path);

    QGraphicsTextItem *pauseTitleText;
    QGraphicsTextItem *pauseScoreText;
    QGraphicsTextItem *whyYouDied;
    Button *backToPlayButton;
    Button *mainMenuButton;

    // music
    void setsound(QString path, int type, int loopCount = 0);

    QGraphicsTextItem *difficultyDisplay;

    QSoundEffect musicJukebox;
    QSoundEffect interfaceJukebox;
    QSoundEffect voiceJukebox;
    QSoundEffect playerJukebox;
    QSoundEffect enemyJukebox;

    float generalVolume;
    float musicVolume;
    int interfaceVolume;
    float voiceVolume;
    float playerVolume;
    float enemyVolume;

    float getMusicVolume();
    float getInterfaceVolume();
    float getVoiceVolume();
    float getPlayerVolume();
    float getEnemyVolume();

public slots:
    void fullscreen();
    void display();
    void displayMenu();
    void displaySettings();
    void displayPause();
    void displayWin();
    void displayGameOver(int reasonIndex);
    void backToPlay();
    void launchGame();
    void setGeneralVolume(int newVolume);
    void setMusicVolume(int newVolume);
    void setInterfaceVolume(int newVolume);
    void setVoiceVolume(int newVolume);
    void setPlayerVolume(int newVolume);
    void setEnemyVolume(int newVolume);
    void setDifficulty(int newDifficulty);
    void setUnlimited(bool newCheckBoxState);
};

#endif // GAME_H
