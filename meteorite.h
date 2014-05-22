#ifndef SATELLITE_H
#define SATELLITE_H

#include "opengl.h"
#include "engineobject.h"


class Meteorite: public EngineObject
{
public:
    Meteorite(GLfloat x,GLfloat y,GLfloat z);
    virtual void render();
    virtual GLfloat getSize();
    static const GLfloat SIZE=0.1;
    void move(); //TODO

private:
    GLUquadric *quad;
};

#endif // SATELLITE_H
