#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat x1, GLfloat y1, GLfloat z1) :
  eyeX(x), eyeY(y), eyeZ(z), forwardX(x1), forwardY(y1), forwardZ(z1)
{

}

GLfloat Camera::getEyeX()
{
  return this->eyeX;
}

GLfloat Camera::getEyeY()
{
  return this->eyeY;
}

GLfloat Camera::getEyeZ()
{
  return this->eyeZ;
}

GLfloat Camera::getForwardX()
{
  return this->forwardX;
}

GLfloat Camera::getForwardY()
{
  return this->forwardY;
}

GLfloat Camera::getForwardZ()
{
  return this->forwardZ;
}


void Camera::setEye (GLfloat x, GLfloat y, GLfloat z)
{
  this->eyeX = x;
  this->eyeY = y;
  this->eyeZ = z;
}

void Camera::setForward (GLfloat x, GLfloat y, GLfloat z)
{
  this->forwardX = x;
  this->forwardY = y;
  this->forwardZ = z;
}

void Camera::render()
{
  gluLookAt(this->eyeX, this->eyeY, this->eyeZ, this->forwardX , this->forwardY , this->forwardZ, 0.0, 0.0,1.0);
}
