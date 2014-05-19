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
    bool isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<AbstractEngineObject *> &engineObject);
    void addRandomCheckpoints(int numberOfCheckpoint);
    void addRandomMeteorites(int numberOfMeteorite);
private:
    GameEngine* gm;
    Sky* sky;
};

#endif // PREPARATIONGAME_H
