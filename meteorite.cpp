#include "meteorite.h"

Meteorite::Meteorite(GLfloat x_, GLfloat y_, GLfloat z_) :
    EngineObject(x_,y_,z_)
{
    quad = gluNewQuadric();
}

void Meteorite::render()
{
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glClear(GL_COLOR);
    glColor4f(1.0,0.0,0.0,1.0);
    gluSphere(this->quad, Meteorite::SIZE*2, 30, 30);
}

GLfloat Meteorite::getSize()
{
    return Meteorite::SIZE;
}

bool Meteorite::hit(GLfloat playerX ,GLfloat playerY,GLfloat playerZ)
{
    GLfloat x=getPositionX();
    GLfloat y=getPositionY();
    GLfloat z=getPositionZ();
    if(getPositionX()<playerX)
        x+=SPEED_SATELLITE;
    else
        x-=SPEED_SATELLITE;
    if(getPositionY()<playerY)
        y+=SPEED_SATELLITE;
    else
        y-=SPEED_SATELLITE;
    if(getPositionZ()<playerZ)
        z+=SPEED_SATELLITE;
    else
        z-=SPEED_SATELLITE;
    setPosition(x,y,z);
    if((int)x==(int)playerX && (int)y==(int)playerY && (int)z==(int)playerZ)
        return true;
    return false;
}
