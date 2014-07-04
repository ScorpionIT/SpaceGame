#include "checkpoint.h"

Checkpoint::Checkpoint(GLfloat x, GLfloat y, GLfloat z, bool active_)
{
    setPosition (x, y, z);
    setSize(SIZE, SIZE, SIZE);
    active=active_;
    quad = gluNewQuadric();
    quad2 = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
}
void Checkpoint::render()
{
    glPushMatrix();
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glColor4f(0.5,0.5,0.0,1.0);
    if(!active)
    {
        gluSphere(quad,Checkpoint::SIZE, 7, 7);
    }
    else
        gluSphere(quad2,Checkpoint::SIZE, 30, 30);
    glPopMatrix();
}

void Checkpoint::setActive(bool active_)
{
    active=active_;
}

bool Checkpoint::isActive()
{
    return active;
}

