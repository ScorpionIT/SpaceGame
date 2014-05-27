#ifndef EARTH_H
#define EARTH_H

#include "engineobject.h"
#include <QTimer>

class Earth : public EngineObject
{
    Q_OBJECT

public:
    Earth(GameEngine* gm, GLfloat x=0, GLfloat y=0, GLfloat z=0, GLfloat size=3);
    virtual void render();
    GLfloat getSize();
    void stop();

private:
    GLfloat size;
    GLuint textureId;
    GLfloat rotationAngle;
    QTimer *timer;

public slots:
  void rotate();
};

#endif // EARTH_H
