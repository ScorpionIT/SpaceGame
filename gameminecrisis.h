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

class GameMineCrisis
{
public:
    GameMineCrisis();
    void start();
    bool isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject);
    void addRandomCheckpoints();
    void addRandomMeteorites();
    void moveMeteorites();
    static const int NUMBER_OF_CHECKPOINT=20;
    static const int NUMBER_OF_METEORITE=100;
private:
    GameEngine* gm;
    Camera* camera;
    Sky* sky;
    Player* player;
    QVector<EngineObject*> meteorites;
    QVector<EngineObject*> checkpoints;
};

#endif // GAMEMINECRISIS_H
