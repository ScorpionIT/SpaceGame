#ifndef SATELLITE_H
#define SATELLITE_H

#include "opengl.h"
#include "engineobject.h"
#include "camera.h"


class Meteorite: public EngineObject
{
public:
    Meteorite(GLfloat x,GLfloat y,GLfloat z);
    virtual void render();
    virtual GLfloat getSize();
    static const GLfloat SIZE=3;
    static const GLfloat SPEED_SATELLITE=0.1;
    bool hit(GLfloat playerX ,GLfloat playerY,GLfloat playerZ);

private:
    GLUquadric *quad;
};

#endif // SATELLITE_H
