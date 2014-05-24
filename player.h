#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "modelloader.h"
#include "camera.h"
#include "gameengine.h"
#include "sky.h"
#include <cmath>
class Player : public EngineObject
{
    Q_OBJECT
public:
    Player(Camera* camera_,GameEngine* gm_,Sky* sky);
    virtual bool hasTexture();
    virtual QString getTexturePath();
    virtual void render();
    virtual GLfloat getSize();
    void stop();
    void start();
    GLfloat getShiftX();
    GLfloat getShiftY();
    GLfloat getShiftZ();

private:
    bool isInsideSky(GLdouble px,GLdouble py,GLdouble pz);
    GameEngine* gm;
    Camera* camera;
    Sky* sky;
    ModelLoader* model;
    bool seeLeft;
    bool seeRight;
    bool seeUp;
    bool seeDown;
    bool moveUp;
    bool incrementShift;
    bool decrementShift;
    bool moveWhingRight;
    bool moveWhingUp;
    GLfloat  shift ;
    GLint   rotateXY ;
    GLfloat   rotateXZ ;
    GLint whingAngle;
    const GLfloat MAX_SPEED;
    const GLfloat MIN_SPEED;
    QTimer *timer;
    bool stopMove;

signals:

public slots:
    void moveOn(QString direction);
    void moveOff(QString direction);
    void move();


};

#endif // PLAYER_H
