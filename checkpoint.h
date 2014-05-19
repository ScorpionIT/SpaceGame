#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "engineobject.h"
#include "GL/glu.h"

class Checkpoint: public EngineObject
{
    Q_OBJECT

public:
    Checkpoint(GLfloat x,GLfloat y,GLfloat z);
    virtual void render();
    static const GLint SIZE=20;
    static const GLint DISTANCE=SIZE*10;
private:
    GLUquadric *quad;
};

#endif // CHECKPOINT_H
