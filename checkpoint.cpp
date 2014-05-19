#include "checkpoint.h"

Checkpoint::Checkpoint(GLfloat x_, GLfloat y_, GLfloat z_) :
    EngineObject(x_,y_,z_)
{
    quad = gluNewQuadric();
}
void Checkpoint::render()
{
    glPushMatrix();
    //glPushAttrib(GL_COLOR_BUFFER_BIT);
    //gluQuadricTexture(this->quad, true);
    glColor4f(0.5,0.5,0.0,1.0);
    gluSphere(this->quad, Checkpoint::SIZE, 100, 100);
    //glPopAttrib();
    glPopMatrix();
}




