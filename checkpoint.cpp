#include "checkpoint.h"

Checkpoint::Checkpoint(GameEngine* gm, GLfloat x, GLfloat y, GLfloat z, bool active_) :
    EngineObject(gm)
{
    setPosition (x, y, z);
    active=active_;
}
void Checkpoint::render()
{
    gm->pushMatrix();
    gm->Translate(getPositionX(),getPositionY(),getPositionZ());
    gm->setColor(0.5,0.5,0.0,1.0);
    if(!active)
        gm->drawSphere(gm->sphereSettings(false, true), Checkpoint::SIZE*2, 7, 7);
    else
        gm->drawSphere(gm->sphereSettings(false,false), Checkpoint::SIZE*2, 30, 30);
    gm->popMatrix();
}

GLfloat Checkpoint::getSize()
{
    return SIZE;
}

void Checkpoint::setActive(bool active_)
{
    active=active_;
}

