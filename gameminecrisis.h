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

class GameMineCrisis:public QObject
{
    Q_OBJECT
public slots:
    void update();
public:
    GameMineCrisis();
    void start();
    void addRandomObstacles();
    void addRandomCheckpoints();
    void addRandomMeteorites();
    void gameOver();
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
    QTimer *timer;
    int numberOfcheckpoint;
};

#endif // GAMEMINECRISIS_H
