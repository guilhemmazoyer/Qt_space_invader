#include "game.h"
#include "button.h"
#include <windows.h>
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QApplication>
#include <QScreen>

Game::Game(QWidget * parent) {
    QSize displaySize = QApplication::screens()[0]->size();
    sceneHeight = displaySize.height();
    sceneWidth = displaySize.width();

    // sound setup
    QSoundEffect jukebox;
    QSoundEffect interfaceMusic;
    generalVolume = 100;
    musicVolume = 100;
    interfaceVolume = 100;

    // create new scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    setScene(scene);

    // set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWindowState(Qt::WindowFullScreen);

    setFixedSize(sceneWidth, sceneHeight);

    fullscreenState = true;
    this->showFullScreen();
}

void Game::display(){
    setsound("../assets/sounds/menu.wav", 0);
    jukebox.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString("../assets/images/space.jpg"));

    // create title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
    QColor yellowTitleColor(226, 215, 73);
    titleText->setDefaultTextColor(yellowTitleColor);
    QFont titleFont("consolas", 80);

    titleText->setFont(titleFont);
    float xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    float yTitlePos = sceneHeight/4.8;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // create play button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    Button *playButton = new Button(QString("Play"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
    qreal yPlayPos = sceneHeight/2.6182;
    playButton->setPos(xPlayPos, yPlayPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(launchGame()));
    scene->addItem(playButton);

    // create settings button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("Settings"), b_width, b_height);
    float xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    float ySettingsPos = sceneHeight/2.0571;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(displaySettings()));
    scene->addItem(settingsButton);

    // create quit button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Quit"), b_width, b_height);
    float xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = sceneHeight/1.6941;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayMenu(){
    setsound("../assets/sounds/click_cancel.wav", 1, 1);
    interfaceMusic.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString("../assets/images/space.jpg"));

    // create title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
    QColor yellowTitleColor(226, 215, 73);
    titleText->setDefaultTextColor(yellowTitleColor);
    QFont titleFont("consolas", 80);

    titleText->setFont(titleFont);
    qreal xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    qreal yTitlePos = sceneHeight/4.8;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // create play button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    Button *playButton = new Button(QString("Play"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
    qreal yPlayPos = sceneHeight/2.6182;
    playButton->setPos(xPlayPos, yPlayPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(launchGame()));
    scene->addItem(playButton);

    // create settings button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("Settings"), b_width, b_height);
    qreal xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    qreal ySettingsPos = sceneHeight/2.0571;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(displaySettings()));
    scene->addItem(settingsButton);

    // create quit button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Quit"), b_width, b_height);
    qreal xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    qreal yQuitPos = sceneHeight/1.6941;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displaySettings(){
    setsound("../assets/sounds/click2.wav", 1, 1);
    interfaceMusic.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString("../assets/images/space.jpg"));

    // create fullscreen button
    qreal b_width = sceneWidth/3;
    qreal b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("Fullscreen"), b_width, b_height);
    qreal xSettingsPos = sceneWidth/2 - settingsButton->boundingRect().width()/2;
    qreal ySettingsPos = sceneHeight/6.5;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(fullscreen()));
    scene->addItem(settingsButton);

    // sound options
        // text items
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("SOUND DESIGN"));
    QGraphicsTextItem *musicTitleText = new QGraphicsTextItem(QString("Music"));
    QGraphicsTextItem *interfaceTitleText = new QGraphicsTextItem(QString("Interface"));
    QGraphicsTextItem *playerTitleText = new QGraphicsTextItem(QString("Player"));
    QGraphicsTextItem *enemyTitleText = new QGraphicsTextItem(QString("Enemy"));
        // pos creation
    qreal xTitlePos;
    qreal yTitlePos;
        // color settings
    titleText->setDefaultTextColor(Qt::white);
    musicTitleText->setDefaultTextColor(Qt::white);
    interfaceTitleText->setDefaultTextColor(Qt::white);
    playerTitleText->setDefaultTextColor(Qt::white);
    enemyTitleText->setDefaultTextColor(Qt::white);
        // font settings
    QFont titleFont("consolas", 40);
    QFont sliderTitleFont("consolas", 30);
    titleText->setFont(titleFont);
    musicTitleText->setFont(sliderTitleFont);
    interfaceTitleText->setFont(sliderTitleFont);
    playerTitleText->setFont(sliderTitleFont);
    enemyTitleText->setFont(sliderTitleFont);

        // title
    xTitlePos = sceneWidth/2 - titleText->boundingRect().width()/2;
    yTitlePos = sceneHeight/4;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

        // shared parameters
    yTitlePos = sceneHeight/3.2;

        // music title + slider
    xTitlePos = sceneWidth/2 - musicTitleText->boundingRect().width()/2 - 300;
    musicTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(musicTitleText);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setGeometry(10, 60, 150, 20);
    slider->setRange(0, 100);
    show();

        // interface title + slider
    xTitlePos = sceneWidth/2 - interfaceTitleText->boundingRect().width()/2 - 100;
    interfaceTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(interfaceTitleText);

        // player title + slider
    xTitlePos = sceneWidth/2 - playerTitleText->boundingRect().width()/2 + 100;
    playerTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(playerTitleText);

        // enemy title + slider
    xTitlePos = sceneWidth/2 - enemyTitleText->boundingRect().width()/2 + 300;
    enemyTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(enemyTitleText);

    // create back button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Back to main menu"), b_width, b_height);
    float xQuitPos = sceneWidth/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = sceneHeight/1.5;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(displayMenu()));
    scene->addItem(quitButton);
}

void Game::launchGame(){
    setsound("../assets/sounds/click1.wav", 1, 1);
    interfaceMusic.play();
    setsound("../assets/sounds/level1.wav", 1, 1);
    jukebox.play();
}

void Game::fullscreen(){
    if(fullscreenState){
        fullscreenState = false;
        this->setWindowState(Qt::WindowMaximized);
        this->showMaximized();

    }else{
        fullscreenState = true;
        this->setWindowState(Qt::WindowFullScreen);
        this->showFullScreen();
    }
    displaySettings();
}

void Game::changeBackground(QString path){
    QPixmap space(path);
    space = space.scaled(sceneWidth, sceneHeight, Qt::IgnoreAspectRatio);
    scene->addPixmap(space);
}

void Game::setsound(QString path, int type, int loopCount){
    if(!loopCount){
        loopCount = QSoundEffect::Infinite;
    }
    switch (type) {
        case 0: // music
            jukebox.setSource(QUrl::fromLocalFile(path));
            jukebox.setLoopCount(loopCount);
            jukebox.setMuted(false);
            jukebox.setVolume(getMusicVolume());
            break;

        case 1: // interface
            interfaceMusic.setSource(QUrl::fromLocalFile(path));
            interfaceMusic.setLoopCount(loopCount);
            interfaceMusic.setMuted(false);
            interfaceMusic.setVolume(getInterfaceVolume());
            break;

        default:
            interfaceMusic.setVolume(getInterfaceVolume());
            break;
    }
}

float Game::getMusicVolume(){
    return ((generalVolume/10)*(musicVolume/10))/100;
}

float Game::getInterfaceVolume(){
    return ((generalVolume/10)*(interfaceVolume/10))/100;
}
