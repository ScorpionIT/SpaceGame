#ifndef PREPARATIONGAME_H
#define PREPARATIONGAME_H
#include <QTime>
#include <QDebug>
#include "sky.h"
#include "gameengine.h"
#include "meteorite.h"
#include "checkpoint.h"
#include "camera.h"
#include "player.h"
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
    int isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject);
    void addRandomCheckpoints();
    void addRandomMeteorites();
    void gameOver();
    static const int NUMBER_OF_CHECKPOINT=20;
    static const int NUMBER_OF_METEORITE=1;
private:
    GameEngine* gm;
    Camera* camera;
    Sky* sky;
    Player* player;
    QVector<EngineObject*> meteorites;
    QVector<EngineObject*> checkpoints;
    GLfloat timerGame;
    QTimer *timer;
    int numberOfcheckpoint;
};

#endif // GAMEMINECRISIS_H
