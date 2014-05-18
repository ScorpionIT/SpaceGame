#include "checkpoint.h"

Checkpoint::Checkpoint(GLfloat x_, GLfloat y_, GLfloat z_,bool active_):AbstractEngineObject(x_,y_,z_)
{
    quad = gluNewQuadric();
    active=active_;
}
void Checkpoint::render()
{
    glPushMatrix();
    glColor4f(0.5,0.5,0.0,1.0);
    gluSphere(this->quad, Checkpoint::SIZE, 100, 100);
    glPopMatrix();
}

GLfloat Checkpoint::getSize()
{
    return SIZE;
}




