#ifndef PREPARATIONGAME_H
#define PREPARATIONGAME_H
#include <QTime>
#include <QDebug>
#include "sky.h"
#include "gameengine.h"
#include "meteorite.h"
#include "checkpoint.h"


class GameMineCrisis
{
public:
    GameMineCrisis(GameEngine* gameEngine,Sky* sky);
    bool isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject);
    void addRandomCheckpoints();
    void addRandomMeteorites();
    static const int NUMBER_OF_CHECKPOINT=20;
    static const int NUMBER_OF_METEORITE=100;
private:
    GameEngine* gm;
    Sky* sky;
};

#endif // PREPARATIONGAME_H
