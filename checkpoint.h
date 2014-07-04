#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "opengl.h"
#include "engineobject.h"

class Checkpoint: public EngineObject
{
    Q_OBJECT

public:
    Checkpoint(GLfloat x,GLfloat y,GLfloat z,bool active=true);
    virtual void render();
    void setActive(bool active_);
    bool isActive();
    static const GLint SIZE=40;
    static const GLint DISTANCE=SIZE*15;
    static const GLint ADDITIONAL_TIME=10;

private:
    GLUquadric* quad;
    GLUquadric* quad2;
    bool active;
};

#endif // CHECKPOINT_H
