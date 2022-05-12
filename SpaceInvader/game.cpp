#include "game.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QSlider>
#include <QCheckBox>
#include <QGraphicsProxyWidget>

Game::Game() {
    QSize displaySize = QApplication::screens()[0]->size();
    sceneHeight = displaySize.height();
    sceneWidth = displaySize.width();
    spaceshipWidthOffset = 41;
    difficulty = 10;

    fullscreenState = true;
    isPauseMenuClosed = true;
    isUnlimited = false;

    // sound setup
    QSoundEffect jukebox;
    QSoundEffect interfaceMusic;
    generalVolume = 100;
    musicVolume = 100;
    interfaceVolume = 100;
    voiceVolume = 100;
    playerVolume = 100;
    enemyVolume = 100;

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
    setsound(":/sounds/menu.wav", 0);
    musicJukebox.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString(":/images/game.jpg"));

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
    setsound(":/sounds/click_cancel.wav", 1, 1);
    interfaceJukebox.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString(":/images/game.jpg"));

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
    setsound(":/sounds/click2.wav", 1, 1);
    interfaceJukebox.play();

    // clean up the screen
    scene->clear();

    changeBackground(QString(":/images/game.jpg"));

    // create fullscreen button
    qreal b_width = sceneWidth/3;
    qreal b_height = sceneHeight/14;
    Button *settingsButton = new Button(QString("Fullscreen"), b_width, b_height);
    qreal xSettingsPos = sceneWidth/2 - settingsButton->boundingRect().width()/2;
    qreal ySettingsPos = sceneHeight/14;
    settingsButton->setPos(xSettingsPos, ySettingsPos);
    connect(settingsButton, SIGNAL(clicked()), this, SLOT(fullscreen()));
    scene->addItem(settingsButton);

    // difficulty options
    QGraphicsTextItem *difficultyTitleText = new QGraphicsTextItem(QString("DIFFICULTY"));
    difficultyTitleText->setDefaultTextColor(Qt::white);
    QFont difficultyTitleFont("consolas", 40);
    difficultyTitleText->setFont(difficultyTitleFont);
    difficultyTitleText->setPos(sceneWidth/2 - difficultyTitleText->boundingRect().width()/2, sceneHeight/5.5);
    scene->addItem(difficultyTitleText);

    difficultyDisplay = new QGraphicsTextItem(QString("xxxxx"));
    difficultyDisplay->setDefaultTextColor(Qt::yellow);
    QFont difficultyDisplayFont("consolas", 20);
    difficultyDisplay->setFont(difficultyDisplayFont);
    difficultyDisplay->setPos(sceneWidth/2 - difficultyDisplay->boundingRect().width()/2, sceneHeight/3.5);
    setDifficulty(difficulty); // show the right name after changing the difficulty
    scene->addItem(difficultyDisplay);

    QSlider *difficultySlider = new QSlider(Qt::Horizontal);
    difficultySlider->setRange(0, 20);
    difficultySlider->setValue(difficulty);
    difficultySlider->setFixedHeight(sceneHeight/40);
    difficultySlider->setFixedWidth(sceneWidth/3);
    QGraphicsProxyWidget * difficultyItem = scene->addWidget(difficultySlider);
    difficultyItem->setPos(sceneWidth/2 - difficultyItem->boundingRect().width()/2,sceneHeight/4);
    connect(difficultySlider, SIGNAL(valueChanged(int)), this, SLOT(setDifficulty(int)));

    // unlimited option
    QCheckBox *unlimitedCheckBox = new QCheckBox(QString("Unlimited Mode"));
    QFont unlimitedCheckBoxFont("consolas", 20);
    unlimitedCheckBox->setFont(unlimitedCheckBoxFont);
    unlimitedCheckBox->setChecked(isUnlimited);
    QGraphicsProxyWidget * unlimitedItem = scene->addWidget(unlimitedCheckBox);
    unlimitedItem->setPos(sceneWidth/2 - unlimitedItem->boundingRect().width()/2,sceneHeight/3);
    connect(unlimitedCheckBox, SIGNAL(toggled(bool)), this, SLOT(setUnlimited(bool)));

    // sound options
        // text items
    QGraphicsTextItem *soundTitleText = new QGraphicsTextItem(QString("SOUND"));
    QGraphicsTextItem *generalTitleText = new QGraphicsTextItem(QString("General"));
    QGraphicsTextItem *musicTitleText = new QGraphicsTextItem(QString("Music"));
    QGraphicsTextItem *interfaceTitleText = new QGraphicsTextItem(QString("Interface"));
    QGraphicsTextItem *voiceTitleText = new QGraphicsTextItem(QString("Voice"));
    QGraphicsTextItem *playerTitleText = new QGraphicsTextItem(QString("Player"));
    QGraphicsTextItem *enemyTitleText = new QGraphicsTextItem(QString("Enemy"));

        // pos creation
    qreal xTitlePos;
    qreal yTitlePos;

        // color settings
    soundTitleText->setDefaultTextColor(Qt::white);
    generalTitleText->setDefaultTextColor(Qt::white);
    musicTitleText->setDefaultTextColor(Qt::white);
    interfaceTitleText->setDefaultTextColor(Qt::white);
    voiceTitleText->setDefaultTextColor(Qt::white);
    playerTitleText->setDefaultTextColor(Qt::white);
    enemyTitleText->setDefaultTextColor(Qt::white);

        // font settings
    QFont titleFont("consolas", 40);
    QFont sliderTitleFont("consolas", 30);
    soundTitleText->setFont(titleFont);
    generalTitleText->setFont(sliderTitleFont);
    musicTitleText->setFont(sliderTitleFont);
    interfaceTitleText->setFont(sliderTitleFont);
    voiceTitleText->setFont(sliderTitleFont);
    playerTitleText->setFont(sliderTitleFont);
    enemyTitleText->setFont(sliderTitleFont);

        // title
    xTitlePos = sceneWidth/2 - soundTitleText->boundingRect().width()/2;
    yTitlePos = sceneHeight/2.2;
    soundTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(soundTitleText);

        // shared parameters
    yTitlePos = sceneHeight/1.9;

        // general title + slider
    xTitlePos = sceneWidth/2 - generalTitleText->boundingRect().width()/2 - (sceneWidth/10)*3 + sceneWidth/20;
    generalTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(generalTitleText);

    QSlider *generalSlider = new QSlider(Qt::Vertical);
    generalSlider->setRange(0, 100);
    generalSlider->setValue(generalVolume);
    generalSlider->setFixedHeight(sceneHeight/6.8);
    generalSlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * item = scene->addWidget(generalSlider);
    item->setPos(sceneWidth/2 - item->boundingRect().width()/2 - (sceneWidth/10)*3 + sceneWidth/20,sceneHeight/1.7);
    connect(generalSlider, SIGNAL(valueChanged(int)), this, SLOT(setGeneralVolume(int)));

        // music title + slider
    xTitlePos = sceneWidth/2 - musicTitleText->boundingRect().width()/2 - (sceneWidth/10)*2 + sceneWidth/20;
    musicTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(musicTitleText);

    QSlider *musicSlider = new QSlider(Qt::Vertical);
    musicSlider->setRange(0, 100);
    musicSlider->setValue(musicVolume);
    musicSlider->setFixedHeight(sceneHeight/6.8);
    musicSlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * musicItem = scene->addWidget(musicSlider);
    musicItem->setPos(sceneWidth/2 - musicItem->boundingRect().width()/2 - (sceneWidth/10)*2 + sceneWidth/20,sceneHeight/1.7);
    connect(musicSlider, SIGNAL(valueChanged(int)), this, SLOT(setMusicVolume(int)));

        // interface title + slider
    xTitlePos = sceneWidth/2 - interfaceTitleText->boundingRect().width()/2 - (sceneWidth/10)*1 + sceneWidth/20;
    interfaceTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(interfaceTitleText);

    QSlider *interfaceSlider = new QSlider(Qt::Vertical);
    interfaceSlider->setRange(0, 100);
    interfaceSlider->setValue(interfaceVolume);
    interfaceSlider->setFixedHeight(sceneHeight/6.8);
    interfaceSlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * interfaceItem = scene->addWidget(interfaceSlider);
    interfaceItem->setPos(sceneWidth/2 - item->boundingRect().width()/2 - (sceneWidth/10)*1 + sceneWidth/20,sceneHeight/1.7);
    connect(interfaceSlider, SIGNAL(valueChanged(int)), this, SLOT(setInterfaceVolume(int)));

        // voice title + slider
    xTitlePos = sceneWidth/2 - voiceTitleText->boundingRect().width()/2 + (sceneWidth/10)*1 - sceneWidth/20;
    voiceTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(voiceTitleText);

    QSlider *voiceSlider = new QSlider(Qt::Vertical);
    voiceSlider->setRange(0, 100);
    voiceSlider->setValue(voiceVolume);
    voiceSlider->setFixedHeight(sceneHeight/6.8);
    voiceSlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * voiceItem = scene->addWidget(voiceSlider);
    voiceItem->setPos(sceneWidth/2 - voiceItem->boundingRect().width()/2 + (sceneWidth/10)*1 - sceneWidth/20,sceneHeight/1.7);
    connect(voiceSlider, SIGNAL(valueChanged(int)), this, SLOT(setVoiceVolume(int)));

        // player title + slider
    xTitlePos = sceneWidth/2 - playerTitleText->boundingRect().width()/2 + (sceneWidth/10)*2 - sceneWidth/20;
    playerTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(playerTitleText);

    QSlider *playerSlider = new QSlider(Qt::Vertical);
    playerSlider->setRange(0, 100);
    playerSlider->setValue(playerVolume);
    playerSlider->setFixedHeight(sceneHeight/6.8);
    playerSlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * playerItem = scene->addWidget(playerSlider);
    playerItem->setPos(sceneWidth/2 - playerItem->boundingRect().width()/2 + (sceneWidth/10)*2 - sceneWidth/20,sceneHeight/1.7);
    connect(playerSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlayerVolume(int)));

        // enemy title + slider
    xTitlePos = sceneWidth/2 - enemyTitleText->boundingRect().width()/2 + (sceneWidth/10)*3 - sceneWidth/20;
    enemyTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(enemyTitleText);

    QSlider *enemySlider = new QSlider(Qt::Vertical);
    enemySlider->setRange(0, 100);
    enemySlider->setValue(enemyVolume);
    enemySlider->setFixedHeight(sceneHeight/6.8);
    enemySlider->setFixedWidth(sceneWidth/75);
    QGraphicsProxyWidget * enemyItem = scene->addWidget(enemySlider);
    enemyItem->setPos(sceneWidth/2 - enemyItem->boundingRect().width()/2 + (sceneWidth/10)*3 - sceneWidth/20,sceneHeight/1.7);
    connect(enemySlider, SIGNAL(valueChanged(int)), this, SLOT(setEnemyVolume(int)));

    // create back button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    Button *quitButton = new Button(QString("Back to main menu"), b_width, b_height);
    float xQuitPos = sceneWidth/2 - quitButton->boundingRect().width()/2;
    float yQuitPos = sceneHeight/1.2;
    quitButton->setPos(xQuitPos, yQuitPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(displayMenu()));
    scene->addItem(quitButton);
}

void Game::displayWin(){
    setsound(":/sounds/win.wav", 2, 1);
    voiceJukebox.play();

    isPauseMenuClosed = false;

    // create title text
    pauseTitleText = new QGraphicsTextItem(QString("You Won !"));
    pauseTitleText->setDefaultTextColor(Qt::green);

    QFont titleFont("consolas", 100);
    pauseTitleText->setFont(titleFont);

    float xTitlePos = this->width()/2 - pauseTitleText->boundingRect().width()/2;
    float yTitlePos = sceneHeight/7;
    pauseTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseTitleText);

    whyYouDied = new QGraphicsTextItem("You wiped out the majority of the aliens");

    whyYouDied->setDefaultTextColor(Qt::darkGreen);
    QFont reasonFont("consolas", 40);
    whyYouDied->setFont(reasonFont);

    xTitlePos = this->width()/2 - whyYouDied->boundingRect().width()/2;
    yTitlePos = sceneHeight/3.6;
    whyYouDied->setPos(xTitlePos, yTitlePos);
    scene->addItem(whyYouDied);

    // create retry button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    Button *retryButton = new Button(QString("Restart"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - retryButton->boundingRect().width()/2;
    qreal yPlayPos = sceneHeight/2.6182;
    retryButton->setPos(xPlayPos, yPlayPos);
    connect(retryButton, SIGNAL(clicked()), this, SLOT(launchGame()));
    scene->addItem(retryButton);

    // create main menu button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    mainMenuButton = new Button(QString("Main Menu"), b_width, b_height);
    float xSettingsPos = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    float ySettingsPos = sceneHeight/2.0571;
    mainMenuButton->setPos(xSettingsPos, ySettingsPos);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(display()));
    scene->addItem(mainMenuButton);

    // score text
    pauseScoreText = new QGraphicsTextItem(QString("Score: ") + QString::number(score->getScore()));
    pauseScoreText->setDefaultTextColor(Qt::blue);
    QFont ScoreFont("consolas", 60);
    pauseScoreText->setFont(ScoreFont);
    xTitlePos = this->width()/2 - pauseScoreText->boundingRect().width()/2;
    yTitlePos = sceneHeight/1.6;
    pauseScoreText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseScoreText);
}

void Game::displayGameOver(int reasonIndex){
    setsound(":/sounds/gameover.wav", 2, 1);
    voiceJukebox.play();

    isPauseMenuClosed = false;

    // create title text
    pauseTitleText = new QGraphicsTextItem(QString("Game Over"));
    pauseTitleText->setDefaultTextColor(Qt::darkRed);

    QFont titleFont("consolas", 100);
    pauseTitleText->setFont(titleFont);

    float xTitlePos = this->width()/2 - pauseTitleText->boundingRect().width()/2;
    float yTitlePos = sceneHeight/7;
    pauseTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseTitleText);

    // create reason text
    switch(reasonIndex) {
        case 0:
            whyYouDied = new QGraphicsTextItem("An alien destroy your spaceship");
            explosion = new Explosion();
            explosion->setPos(player->x() - 18, player->y()-50);
            scene->addItem(explosion);
            break;
        case 1:
            whyYouDied = new QGraphicsTextItem("Too many aliens have passed");
            break;
        default :
            whyYouDied = new QGraphicsTextItem("You lose !");
    }

    whyYouDied->setDefaultTextColor(Qt::red);
    QFont reasonFont("consolas", 40);
    whyYouDied->setFont(reasonFont);

    xTitlePos = this->width()/2 - whyYouDied->boundingRect().width()/2;
    yTitlePos = sceneHeight/3.6;
    whyYouDied->setPos(xTitlePos, yTitlePos);
    scene->addItem(whyYouDied);

    // create retry button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    Button *retryButton = new Button(QString("Retry"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - retryButton->boundingRect().width()/2;
    qreal yPlayPos = sceneHeight/2.6182;
    retryButton->setPos(xPlayPos, yPlayPos);
    connect(retryButton, SIGNAL(clicked()), this, SLOT(launchGame()));
    scene->addItem(retryButton);

    // create main menu button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    mainMenuButton = new Button(QString("Main Menu"), b_width, b_height);
    float xSettingsPos = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    float ySettingsPos = sceneHeight/2.0571;
    mainMenuButton->setPos(xSettingsPos, ySettingsPos);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(display()));
    scene->addItem(mainMenuButton);

    // score text
    pauseScoreText = new QGraphicsTextItem(QString("Score: ") + QString::number(score->getScore()));
    pauseScoreText->setDefaultTextColor(Qt::blue);
    QFont ScoreFont("consolas", 60);
    pauseScoreText->setFont(ScoreFont);
    xTitlePos = this->width()/2 - pauseScoreText->boundingRect().width()/2;
    yTitlePos = sceneHeight/1.6;
    pauseScoreText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseScoreText);
}

void Game::displayPause(){
    setsound(":/sounds/click2.wav", 1, 1);
    interfaceJukebox.play();

    isPauseMenuClosed = false;

    // create title text
    pauseTitleText = new QGraphicsTextItem(QString("Pause"));
    pauseTitleText->setDefaultTextColor(Qt::white);

    QFont titleFont("consolas", 60);
    pauseTitleText->setFont(titleFont);

    float xTitlePos = this->width()/2 - pauseTitleText->boundingRect().width()/2;
    float yTitlePos = sceneHeight/4.8;
    pauseTitleText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseTitleText);

    // create back to play button
    float b_width = sceneWidth/3;
    float b_height = sceneHeight/12;
    backToPlayButton = new Button(QString("Back to game"), b_width, b_height);
    qreal xPlayPos = this->width()/2 - backToPlayButton->boundingRect().width()/2;
    qreal yPlayPos = sceneHeight/2.6182;
    backToPlayButton->setPos(xPlayPos, yPlayPos);
    connect(backToPlayButton, SIGNAL(clicked()), this, SLOT(backToPlay()));
    scene->addItem(backToPlayButton);

    // create main menu button
    b_width = sceneWidth/3;
    b_height = sceneHeight/12;
    mainMenuButton = new Button(QString("Main Menu"), b_width, b_height);
    float xSettingsPos = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    float ySettingsPos = sceneHeight/2.0571;
    mainMenuButton->setPos(xSettingsPos, ySettingsPos);
    connect(mainMenuButton, SIGNAL(clicked()), this, SLOT(display()));
    scene->addItem(mainMenuButton);

    // score text
    pauseScoreText = new QGraphicsTextItem(QString("Score: ") + QString::number(score->getScore()));
    pauseScoreText->setDefaultTextColor(Qt::blue);
    QFont ScoreFont("consolas", 60);
    pauseScoreText->setFont(ScoreFont);
    xTitlePos = this->width()/2 - pauseScoreText->boundingRect().width()/2;
    yTitlePos = sceneHeight/1.6;
    pauseScoreText->setPos(xTitlePos, yTitlePos);
    scene->addItem(pauseScoreText);
}

void Game::launchGame(){
    setsound(":/sounds/start.wav", 2, 1);
    voiceJukebox.play();
    setsound(":/sounds/click1.wav", 1, 1);
    interfaceJukebox.play();
    setsound(":/sounds/level1.wav", 0);
    musicJukebox.play();
    scene->clear();

    isPauseMenuClosed = true;

    changeBackground(QString(":/images/game.jpg"));

    // create the player, make it focusable and add to the scene
    player = new Player();
    player->setFocus();
    scene->addItem(player);

    // delay between two mouvements
    QTimer * playerActionsTimer = new QTimer();
    QObject::connect(playerActionsTimer, SIGNAL(timeout()), player, SLOT(action()));
    int actionsTimeMs = 100;
    playerActionsTimer->start(actionsTimeMs);

    // create the score
    score = new Score();
    scene->addItem(score);

    // Create health
    health = new Health();
    // Position the health 25 pixels below the score
    int yHealthOffset = 25;
    health->setPos(health->x(), health->y() + yHealthOffset);
    scene->addItem(health);

    // Spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

    int spawnTimeMs = 1200 - (difficulty * 30);
    timer->start(spawnTimeMs);
}

void Game::backToPlay() {
    setsound(":/sounds/click1.wav", 1, 1);
    interfaceJukebox.play();

    player->setFocus();
    scene->removeItem(pauseTitleText);
    scene->removeItem(backToPlayButton);
    scene->removeItem(mainMenuButton);
    scene->removeItem(pauseScoreText);
    isPauseMenuClosed = true;
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
            musicJukebox.setSource(QUrl::fromLocalFile(path));
            musicJukebox.setLoopCount(loopCount);
            musicJukebox.setMuted(false);
            musicJukebox.setVolume(getMusicVolume());
            break;

        case 1: // interface
            interfaceJukebox.setSource(QUrl::fromLocalFile(path));
            interfaceJukebox.setLoopCount(loopCount);
            interfaceJukebox.setMuted(false);
            interfaceJukebox.setVolume(getInterfaceVolume());
            break;

        case 2: // voice
            voiceJukebox.setSource(QUrl::fromLocalFile(path));
            voiceJukebox.setLoopCount(loopCount);
            voiceJukebox.setMuted(false);
            voiceJukebox.setVolume(getVoiceVolume());
            break;

        case 3: // player
            playerJukebox.setSource(QUrl::fromLocalFile(path));
            playerJukebox.setLoopCount(loopCount);
            playerJukebox.setMuted(false);
            playerJukebox.setVolume(getPlayerVolume());
            break;

        case 4: // enemy
            enemyJukebox.setSource(QUrl::fromLocalFile(path));
            enemyJukebox.setLoopCount(loopCount);
            enemyJukebox.setMuted(false);
            enemyJukebox.setVolume(getEnemyVolume());
            break;

        default:
            interfaceJukebox.setVolume(getInterfaceVolume());
            break;
    }
}

float Game::getMusicVolume(){
    return ((generalVolume/10)*(musicVolume/10))/100;
}

float Game::getInterfaceVolume(){
    return ((generalVolume/10)*(interfaceVolume/10))/100;
}

float Game::getVoiceVolume(){
    return ((generalVolume/10)*(voiceVolume/10))/100;
}

float Game::getPlayerVolume(){
    return ((generalVolume/10)*(playerVolume/10))/100;
}

float Game::getEnemyVolume(){
    return ((generalVolume/10)*(enemyVolume/10))/100;
}

void Game::setGeneralVolume(int newVolume){
    generalVolume = newVolume;
}

void Game::setMusicVolume(int newVolume){
    musicVolume = newVolume;
    setsound(":/sounds/menu.wav", 0);
    musicJukebox.play();
}

void Game::setInterfaceVolume(int newVolume){
    interfaceVolume = newVolume;
    setsound(":/sounds/click1.wav", 1, 1);
    interfaceJukebox.play();
}

void Game::setVoiceVolume(int newVolume){
    voiceVolume = newVolume;
    setsound(":/sounds/hurt.wav", 2, 1);
    voiceJukebox.play();
}

void Game::setPlayerVolume(int newVolume){
    playerVolume = newVolume;
    setsound(":/sounds/blaster.wav", 3, 1);
    playerJukebox.play();
}

void Game::setEnemyVolume(int newVolume){
    enemyVolume = newVolume;
    setsound(":/sounds/aliendeath.wav", 4, 1);
    enemyJukebox.play();
}

void Game::setDifficulty(int newDifficulty){
    difficulty = newDifficulty;
    if(difficulty<7){ // easy
        difficultyDisplay->setPlainText("easy");
        difficultyDisplay->setDefaultTextColor(Qt::green);

    }else if(difficulty>13){ // hard
        difficultyDisplay->setPlainText("hard");
        difficultyDisplay->setDefaultTextColor(Qt::red);

    }else{ // normal
        difficultyDisplay->setPlainText("normal");
        difficultyDisplay->setDefaultTextColor(Qt::yellow);
    }
}

void Game::setUnlimited(bool newCheckBoxState){
    isUnlimited = newCheckBoxState;
}
