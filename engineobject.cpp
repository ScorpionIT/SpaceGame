#include "engineobject.h"

EngineObject::EngineObject(GLfloat x,GLfloat y,GLfloat z,bool alive_)
{
    setPosition(x,y,z);
    alive=alive_;
}

bool EngineObject::hasTexture()
{
    return false;
}

QString EngineObject::getTexturePath()
{
    return QString();
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

void EngineObject::setAlive(bool alive_)
{
    alive=alive_;
}

bool EngineObject::isAlive()
{
    return alive;
}
