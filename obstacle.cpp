#include "obstacle.h"

Obstacle::Obstacle(GameEngine* gm, GLfloat x, GLfloat y, GLfloat z) :
  EngineObject(gm)
{
    setPosition (x, y, z);
}

void Obstacle::render()
{
    gm->pushMatrix();
    gm->Translate(getPositionX(),getPositionY(),getPositionZ());
    gm->setColor(1, 0, 0, 1);
    gm->drawCube(Obstacle::SIZE);
    gm->popMatrix();
}

GLfloat Obstacle::getSize()
{
    return Obstacle::SIZE;
}
