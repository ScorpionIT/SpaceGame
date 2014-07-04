#ifndef PREPARATIONGAME_H
#define PREPARATIONGAME_H

#include <QFontDatabase>
#include <QMediaPlayer>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QDir>

#include "hudmessagesystem.h"
#include "gameengine.h"
#include "checkpoint.h"
#include "meteorite.h"
#include "obstacle.h"
#include "camera.h"
#include "player.h"
#include "earth.h"
#include "sky.h"


class GameMineCrisis: public QObject
{
    Q_OBJECT

public:
    GameMineCrisis();
    void start(bool connect= true);
    void restart();
    static const int NUMBER_OF_CHECKPOINTS=20;
    static const int NUMBER_OF_METEORITES=100;
    static const int NUMBER_OF_OBSTACLES=50;

private:
    int isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject);
    HudMessageSystem* hms;
    GameEngine* gm;
    Camera* camera;
    Sky* sky;
    Player* player;
    Earth* earth;
    QVector<EngineObject*> meteorites;
    QVector<EngineObject*> checkpoints;
    QVector<EngineObject*> obstacles;
    QFont textFont;
    QString hud_timerGame;
    QString hud_checkpoints;
    QTime timerGameT;
    QTime timerGame;
    QTime startTime;
    QTimer *uTimer;
    QTimer *timer_gameMainLoop;
    QMediaPlayer* backgroundMusic;
    QMediaPlayer* checkpointEffect;
    QMediaPlayer* turboEffect;
    QMediaPlayer* gameOverEffect;
    int numberOfcheckpoint;
    bool gameover;
    bool pause;

    void addRandomObstacles();
    void addRandomCheckpoints();
    void addRandomMeteorites();

private slots:
    void gameOver();
    void gameMainLoop();
    void update();
    void updateTimer ();
    void processKeys(QString key);
    void loopBackgroundMusic(QMediaPlayer::MediaStatus status);
};

#endif // GAMEMINECRISIS_H
