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
    gluSphere(this->quad, Meteorite::SIZE, 30, 30);
    glPopMatrix();
}

GLfloat Meteorite::getSize()
{
    return Meteorite::SIZE;
}

void Meteorite::move(GLfloat playerX ,GLfloat playerY,GLfloat playerZ)
{
    if(getPositionX()<playerX)
        playerX+=SPEED_SATELLITE;
    else
        playerX-=SPEED_SATELLITE;
    if(getPositionY()<playerY)
        playerY+=SPEED_SATELLITE;
    else
        playerY-=SPEED_SATELLITE;
    if(getPositionZ()<playerZ)
        playerZ+=SPEED_SATELLITE;
    else
        playerZ-=SPEED_SATELLITE;
    setPosition(playerX,playerY,playerZ);
}
