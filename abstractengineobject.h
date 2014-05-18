#ifndef ABSTRACTENGINEOBJECT_H
#define ABSTRACTENGINEOBJECT_H

#include <QObject>
#include <GL/gl.h>

class AbstractEngineObject : public QObject
{
  Q_OBJECT
public:
  AbstractEngineObject(QObject *parent = 0);
  virtual bool hasTexture() = 0;
  virtual QString getTexturePath() = 0;
  virtual void render() = 0;
  virtual GLfloat getPositionX();
  virtual GLfloat getPositionY();
  virtual GLfloat getPositionZ();
  virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);

private:
  GLfloat positionX;
  GLfloat positionY;
  GLfloat positionZ;

signals:

public slots:

};

#endif // ABSTRACTENGINEOBJECT_H
