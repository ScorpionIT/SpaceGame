#ifndef SKY_H
#define SKY_H

#include "opengl.h"
#include <QObject>
#include <QString>
#include "engineobject.h"
#include <QTimer>

class Sky : public EngineObject
{
  Q_OBJECT

public:
  Sky(GLfloat size);
  virtual void render();
  void stop();

private:
  GLUquadric* quad;
  GLuint textureId;
  GLfloat rotationAngle;
  QTimer *timer;

signals:

public slots:
  void rotate();

};

#endif // SKY_H
