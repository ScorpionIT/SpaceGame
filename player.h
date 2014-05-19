#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "gameengine.h"
//#include "modelloader.h"

class Player : public EngineObject
{
    Q_OBJECT

public:
    Player();
    virtual void render();

private:
    //ModelLoader* playerObj;
    GLMmodel* model;

signals:

public slots:

};

#endif // PLAYER_H
