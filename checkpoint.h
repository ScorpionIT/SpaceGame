#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include "abstractengineobject.h"
#include "GL/glu.h"
class Checkpoint: public AbstractEngineObject
{
    Q_OBJECT
public:
    Checkpoint(GLfloat x,GLfloat y,GLfloat z,bool active=true);
    virtual void render();
    virtual GLfloat getSize();
    static const GLint SIZE=20;
    static const GLint DISTANCE=SIZE*10;
    static const GLint ADDITIONAL_TIME=10;
private:
    GLUquadric *quad;
    bool active;
};

#endif // CHECKPOINT_H
