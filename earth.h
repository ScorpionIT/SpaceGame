#ifndef EARTH_H
#define EARTH_H
#include "engineobject.h"
#include <QTimer>
#include<QObject>
class Earth:public EngineObject
{
    Q_OBJECT
public slots:
  void rotate();
public:
    Earth(GLfloat x=0,GLfloat y=0,GLfloat z=0,GLfloat size=3);
    void render();
    bool hasTexture();
    QString getTexturePath();
    GLfloat getSize();
    void stop();
private:
    GLfloat size;
    GLUquadric *quad;
    GLfloat rotationAngle;
    QTimer *timer;
};

#endif // EARTH_H
