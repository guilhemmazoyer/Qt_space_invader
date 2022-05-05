#include "game.h"
#include "button.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>

Game::Game(QWidget * parent){
    QRect rec = QApplication::desktop()->screenGeometry();
    sceneHeight = rec.height();
    sceneWidth = rec.width();

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
    // clean up the screen
    scene->clear();

    changeBackground(QString("./images/space.jpg"));

    // create title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
    QColor yellowTitleColor(226, 215, 73);
    titleText->setDefaultTextColor(yellowTitleColor);
    QFont titleFont("consolas", 80);

    titleText->setFont(titleFont);
    float xTitlePos = this->width()/2 - titleText->boundingRect().width()/2;
    float yTitlePos = float(sceneHeight)/4.8;
    titleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(titleText);

    // create play button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    Button *playButton = new Button(QString("Play"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - playButton->boundingRect().width()/2;
    qreal yPlayPos = float(sceneHeight)/2.6182;
    playButton->setPos(xPlayPos, yPlayPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(startGame()));
    scene->addItem(playButton);

    // create settings button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("Settings"), b_width, b_height);
    float xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    float ySettingsPos = float(sceneHeight)/2.0571;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(displaySettings()));
    scene->addItem(settingsButton);

    // create quit button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Quit"), b_width, b_height);
    float xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = float(sceneHeight)/1.6941;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displaySettings(){
    // clean up the screen
    scene->clear();

    changeBackground(QString("./images/space.jpg"));

    // create fullscreen button
    float b_width = sceneWidth/5;
    float b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("Fullscreen"), b_width, b_height);
    float xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    float ySettingsPos = float(sceneHeight)/2.0571;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(fullscreen()));
    scene->addItem(settingsButton);

    // create back button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Back to main menu"), b_width, b_height);
    float xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = float(sceneHeight)/1.6941;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(display()));
    scene->addItem(quitButton);
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
