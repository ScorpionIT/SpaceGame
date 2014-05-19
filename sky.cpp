#include "sky.h"

Sky::Sky(GLfloat size_)
{
  quad = gluNewQuadric();
  setPosition(0, 0, 0);
  this->size=size_;
}

bool Sky::hasTexture()
{
  return true;
}

QString Sky::getTexturePath()
{
  return QString ("data/texture/sky.png");
}

void Sky::render()
{

      gluQuadricTexture(this->quad, true);
      glColor4f(1.0,1.0,1.0,1.0);
      gluSphere(this->quad, this->size, 100, 100);

}

GLfloat Sky::getSize()
{
    return size;
}
