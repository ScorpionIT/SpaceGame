#include "abstractengineobject.h"

AbstractEngineObject::AbstractEngineObject(GLfloat x,GLfloat y,GLfloat z)
{
    setPosition(x,y,z);
}



bool AbstractEngineObject::hasTexture()
{
    return false;
}

QString AbstractEngineObject::getTexturePath()
{
    return QString();
}

GLfloat AbstractEngineObject::getPositionX()
{
    return this->positionX;
}

GLfloat AbstractEngineObject::getPositionY()
{
    return this->positionY;
}

GLfloat AbstractEngineObject::getPositionZ()
{
    return this->positionZ;
}

void AbstractEngineObject::setPosition (GLfloat x, GLfloat y, GLfloat z)
{
    this->positionX = x;
    this->positionY = y;
    this->positionZ = z;
}
