#ifndef PLAYER_H
#define PLAYER_H

#include "engineobject.h"
#include "camera.h"
#include "gameengine.h"
#include "sky.h"
#include "model.h"
#include <cmath>

class Player : public EngineObject
{
    Q_OBJECT
public:
    Player(Camera* camera, Sky* sky);
    virtual void render();
    void reset();
    GLfloat getShiftX();
    GLfloat getShiftY();
    GLfloat getShiftZ();

private:
    bool isInsideSky(GLdouble px,GLdouble py,GLdouble pz);
    Camera* camera;
    Sky* sky;
    Model* model;
    GLuint modelList;
    int modelDepth;
    bool seeLeft;
    bool seeRight;
    bool seeUp;
    bool seeDown;
    bool moveUp;
    bool incrementShift;
    bool decrementShift;
    bool moveWhingRight;
    bool moveWhingUp;
    GLfloat  shift;
    GLint rotateAngleXY;
    GLint   rotateXY ;
    GLfloat rotateAngleXZ;
    GLfloat rotateXZ ;
    GLfloat rotateModelXZ ;
    GLint whingAngle;
    GLint whingAngleStep;
    GLint whingMaxAngle;
    GLfloat tailAngle;
    GLfloat tailAngleStep;
    GLfloat tailMaxAngle;
    const GLfloat MAX_SPEED;
    const GLfloat STANDARD_SPEED;
    const GLfloat MIN_SPEED;
    GLfloat speed;
    QTimer *timer;
    bool stopMove;

signals:
    void turboOn();
    void turboOff();

public slots:
    void moveOn(QString direction);
    void moveOff(QString direction);
    void update();


};

#endif // PLAYER_H
