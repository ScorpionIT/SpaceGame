#include "meteorite.h"

Meteorite::Meteorite(GLfloat x, GLfloat y, GLfloat z)
{
    setPosition(x,y,z);
    setSize(SIZE,SIZE,SIZE);
    quad = gluNewQuadric();
}

void Meteorite::render()
{
    glPushMatrix();
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glColor4f(1.0,0.0,0.0,1.0);
    gluSphere(quad, Meteorite::SIZE, 30, 30);
    glPopMatrix();
    //gluSphere(this->quad, Meteorite::SIZE*2, 30, 30);
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

