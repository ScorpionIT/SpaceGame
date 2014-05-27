#ifndef CAMERA_H
#define CAMERA_H

#include "opengl.h"
#include <QObject>


class Camera : public QObject
{
  Q_OBJECT

public:
  Camera();
  Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat x1, GLfloat y1, GLfloat z1);

  GLfloat getEyeX();
  GLfloat getEyeY();
  GLfloat getEyeZ();
  GLfloat getForwardX();
  GLfloat getForwardY();
  GLfloat getForwardZ();

  void setEye (GLfloat x, GLfloat y, GLfloat z);
  void setForward (GLfloat x, GLfloat y, GLfloat z);

private:
  GLfloat eyeX;
  GLfloat eyeY;
  GLfloat eyeZ;
  GLfloat forwardX;
  GLfloat forwardY;
  GLfloat forwardZ;

signals:

public slots:

};

#endif // CAMERA_H
