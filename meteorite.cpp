#include "meteorite.h"

Meteorite::Meteorite(GameEngine* gm, GLfloat x, GLfloat y, GLfloat z) :
    EngineObject(gm)
{
    setPosition(x,y,z);
    quad = gluNewQuadric();
}

void Meteorite::render()
{
    gm->pushMatrix();
    gm->Translate(getPositionX(),getPositionY(),getPositionZ());
    gm->clearColor();
    gm->setColor(1.0,0.0,0.0,1.0);
    gm->drawSphere(gm->sphereSettings(false,false), Meteorite::SIZE*2, 30, 30);
    gm->popMatrix();
    //gluSphere(this->quad, Meteorite::SIZE*2, 30, 30);
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
