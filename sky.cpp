#include "sky.h"

Sky::Sky()
{
  quad = gluNewQuadric();
  this->x=0;
  this->y=0;
  this->z=0;
  this->size=100;
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPushMatrix();

      gluQuadricTexture(this->quad, true);
      //glColor3f(0.5,0.8,0.9);
      gluSphere(this->quad, this->size, 100, 100);
  glPopMatrix();
}
