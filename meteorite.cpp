#include "meteorite.h"

Meteorite::Meteorite(GLfloat x_, GLfloat y_, GLfloat z_) :
    EngineObject(x_,y_,z_)
{
    quad = gluNewQuadric();
}

void Meteorite::render()
{
    glPushMatrix();
    glColor4f(1.0,0.0,0.0,1.0);
    gluSphere(this->quad, Meteorite::SIZE, 100, 100);
    glPopMatrix();
}

GLfloat Meteorite::getSize()
{
    return Meteorite::SIZE;
}
