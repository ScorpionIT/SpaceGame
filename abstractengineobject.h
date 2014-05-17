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

signals:

public slots:

};

#endif // ABSTRACTENGINEOBJECT_H
