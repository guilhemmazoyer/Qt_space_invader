#include "game.h"
#include "button.h"
#include <iostream>
#include <QDebug>
#include <QTimer>

Game::Game(QWidget * parent){

    sceneWidth = 1280;
    sceneHeight = 720;

    // set up screen
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(sceneWidth, sceneHeight);

    // set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    setScene(scene);
}

void Game::display(){
    // clean up the screen
    scene->clear();

    // create title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("Space Invaders"));
    QFont titleFont("comic sans", 60);
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

    // create display size settings button
        // 480p
    float b_width = sceneWidth/5;
    float b_height = sceneHeight/12;
    Button *lowSettingButton = new Button(QString("480p"), b_width, b_height);
    qreal xPlayPos = this->width()/4 - lowSettingButton->boundingRect().width()/2;
    qreal yPlayPos = float(sceneHeight)/4.8;
    lowSettingButton->setPos(xPlayPos, yPlayPos);
    connect(lowSettingButton, SIGNAL(clicked()), this, SLOT(lowSettings()));
    scene->addItem(lowSettingButton);

        // 720p
    b_width = sceneWidth/5;
    b_height = sceneHeight/12;
    Button *mediumSettingButton = new Button(QString("720p"), b_width, b_height);
    xPlayPos = this->width()/2 - mediumSettingButton->boundingRect().width()/2;
    yPlayPos = float(sceneHeight)/4.8;
    mediumSettingButton->setPos(xPlayPos, yPlayPos);
    connect(mediumSettingButton, SIGNAL(clicked()), this, SLOT(mediumSettings()));
    scene->addItem(mediumSettingButton);

        // 1080p
    b_width = sceneWidth/5;
    b_height = sceneHeight/12;
    Button *highSettingButton = new Button(QString("1080p"), b_width, b_height);
    xPlayPos = this->width()*(0.75) - highSettingButton->boundingRect().width()/2;
    yPlayPos = float(sceneHeight)/4.8;
    highSettingButton->setPos(xPlayPos, yPlayPos);
    connect(highSettingButton, SIGNAL(clicked()), this, SLOT(highSettings()));
    scene->addItem(highSettingButton);

    // create settings button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *settingsButton = new Button(QString("ss"), b_width, b_height);
    float xSettingsPos = this->width()/2 - settingsButton->boundingRect().width()/2;
    float ySettingsPos = float(sceneHeight)/2.0571;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(fullscreen()));
    scene->addItem(settingsButton);

    // create quit button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("qq"), b_width, b_height);
    float xQuitPos = this->width()/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = float(sceneHeight)/1.6941;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(display()));
    scene->addItem(quitButton);
}


void Game::fullscreen(){
    this->setWindowState(Qt::WindowFullScreen);
    this->showFullScreen();
}

void Game::lowSettings(){
    printf("gfd");
    sceneWidth = 853;
    sceneHeight = 480;
    setFixedSize(sceneWidth, sceneHeight);
    displaySettings();
}

void Game::mediumSettings(){
    sceneWidth = 1280;
    sceneHeight = 720;
    setFixedSize(sceneWidth, sceneHeight);
    displaySettings();
}

void Game::highSettings(){
    sceneWidth = 1920;
    sceneHeight = 1080;
    setFixedSize(sceneWidth, sceneHeight);
    displaySettings();
}
