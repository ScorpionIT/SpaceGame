#include "checkpoint.h"

Checkpoint::Checkpoint(GLfloat x_, GLfloat y_, GLfloat z_,bool active_) :
  EngineObject(x_,y_,z_)
{
    quad = gluNewQuadric();
    active=active_;
}
void Checkpoint::render()
{
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    quad = gluNewQuadric();
    glColor4f(0.5,0.5,0.0,1.0);
    if(!active)
    {
        gluQuadricDrawStyle(quad, GLU_LINE);
        gluSphere(this->quad, Checkpoint::SIZE, 7, 7);
    }
    else
        gluSphere(this->quad, Checkpoint::SIZE, 30, 30);
    gluDeleteQuadric(quad);
}

GLfloat Checkpoint::getSize()
{
    return SIZE;
}

void Checkpoint::setActive(bool active_)
{
    active=active_;
}




