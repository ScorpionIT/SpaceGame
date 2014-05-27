#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "camera.h"
#include "gameengine.h"
#include "sky.h"
#include <cmath>

class Player : public EngineObject
{
    Q_OBJECT
public:
    Player(GameEngine* gm, Camera* camera, Sky* sky);
    virtual void render();
    virtual GLfloat getSize();
    void stop();
    void start();
    GLfloat getShiftX();
    GLfloat getShiftY();
    GLfloat getShiftZ();

private:
    bool isInsideSky(GLdouble px,GLdouble py,GLdouble pz);
    Camera* camera;
    Sky* sky;
    Model* model;
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
