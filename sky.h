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
  virtual bool hasTexture();
  virtual QString getTexturePath();
  virtual void render();
  virtual GLfloat getSize();

private:
  GLfloat size;
  GLUquadric *quad;
  GLfloat rotationAngle;

signals:

public slots:
  void rotate();

};

#endif // SKY_H
