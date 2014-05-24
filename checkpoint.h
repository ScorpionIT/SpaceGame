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
    virtual GLfloat getSize();
    void setActive(bool active_);
    static const GLint SIZE=20;
    static const GLint DISTANCE=SIZE*15;
    static const GLint ADDITIONAL_TIME=10;
private:
    GLUquadric *quad;
    bool active;
};

#endif // CHECKPOINT_H
