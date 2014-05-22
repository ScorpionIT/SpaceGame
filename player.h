#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "modelloader.h"
#include "camera.h"
#include "gameengine.h"
#include <cmath>
class Player : public EngineObject
{
    Q_OBJECT
public:
    Player(Camera* camera_,GameEngine* gm_);
    virtual bool hasTexture();
    virtual QString getTexturePath();
    virtual void render();
    virtual GLfloat getSize();

private:
    GameEngine* gm;
    ModelLoader* model;
    Camera* camera;
    bool seeLeft;
    bool seeRight;
    bool seeUp;
    bool seeDown;
    bool moveUp;
    bool incrementShift;
    bool decrementShift;
    bool moveWhingRight;
    GLfloat  shift ;
    GLint   rotateXY ;
    GLfloat   rotateXZ ;
    const GLfloat MAX_SPEED;
    const GLfloat MIN_SPEED;

signals:

public slots:
    void moveOn(QString direction);
    void moveOff(QString direction);
    void move();


};

#endif // PLAYER_H
