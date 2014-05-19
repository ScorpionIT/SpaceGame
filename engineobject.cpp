#include "engineobject.h"

EngineObject::EngineObject(GLfloat x,GLfloat y,GLfloat z)
{
    setPosition(x,y,z);
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
