#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "modelloader.h"

class Player : public EngineObject
{
    Q_OBJECT

public:
    Player();
    virtual bool hasTexture();
    virtual QString getTexturePath();
    virtual void render();
    virtual GLfloat getSize();

private:
    ModelLoader* model;


signals:

public slots:

};

#endif // PLAYER_H
