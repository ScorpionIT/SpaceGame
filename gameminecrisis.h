#ifndef PREPARATIONGAME_H
#define PREPARATIONGAME_H
#include <QTime>
#include <QDebug>
#include "sky.h"
#include "gameengine.h"
#include "meteorite.h"
#include "checkpoint.h"
#include "obstacle.h"
#include "camera.h"
#include "player.h"
#include "earth.h"
#include <QTimer>
#include <QObject>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QDir>

class GameMineCrisis:public QObject
{
    Q_OBJECT

public:
    GameMineCrisis();
    void start();
    static const int NUMBER_OF_CHECKPOINTS=20;
    static const int NUMBER_OF_METEORITES=100;
    static const int NUMBER_OF_OBSTACLES=50;

private:
    int isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject);
    GameEngine* gm;
    Camera* camera;
    Sky* sky;
    Player* player;
    Earth* earth;
    QVector<EngineObject*> meteorites;
    QVector<EngineObject*> checkpoints;
    QVector<EngineObject*> obstacles;
    GLfloat timerGame;
    QString hud_timerGame;
    QString hud_checkpoints;
    QTimer *timer;
    QTimer *timer_gameMainLoop;
    QFont textFont;
    QMediaPlayer* backgroundMusic;
    QMediaPlayer* checkpointEffect;
    QMediaPlayer* turboEffect;
    QMediaPlayer* gameOverEffect;
    int numberOfcheckpoint;
    bool gameover;

    void addRandomObstacles();
    void addRandomCheckpoints();
    void addRandomMeteorites();
    void gameOver();

public slots:
    void gameMainLoop();
    void update();
    void loopBackgroundMusic(QMediaPlayer::MediaStatus status);
    void loopTurboEffect(QMediaPlayer::MediaStatus status);
};

#endif // GAMEMINECRISIS_H
