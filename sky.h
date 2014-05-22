#ifndef SKY_H
#define SKY_H

#include "opengl.h"
#include <QObject>
#include <QString>



#include "engineobject.h"

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

signals:

public slots:

};

#endif // SKY_H
