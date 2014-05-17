#ifndef SKY_H
#define SKY_H

#include <QObject>
#include <QString>
#include <GL/gl.h>
#include <GL/glu.h>

#include "abstractengineobject.h"

class Sky : public AbstractEngineObject
{
  Q_OBJECT

public:
  Sky();
  virtual bool hasTexture();
  virtual QString getTexturePath();
  virtual void render();

private:
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLint size;
  GLUquadric *quad;

signals:

public slots:

};

#endif // SKY_H
