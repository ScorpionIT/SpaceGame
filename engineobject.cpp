#include "engineobject.h"

EngineObject::EngineObject(GameEngine* gm)
{
    this->gm = gm;
}

GLfloat EngineObject::getPositionX()
{
    return this->positionX;
}

GLfloat EngineObject::getPositionY()
{
    return this->positionY;
}

GLfloat EngineObject::getPositionZ()
{
    return this->positionZ;
}

void EngineObject::setPosition (GLfloat x, GLfloat y, GLfloat z)
{
    this->positionX = x;
    this->positionY = y;
    this->positionZ = z;
}
