#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "opengl.h"
#include <QObject>


class EngineObject : public QObject
{
    Q_OBJECT
public:
    EngineObject(GLfloat x=0,GLfloat y=0,GLfloat z=0,bool alive=true);
    virtual bool hasTexture();
    virtual QString getTexturePath();
    virtual GLfloat getPositionX();
    virtual GLfloat getPositionY();
    virtual GLfloat getPositionZ();
    virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);
    virtual void render() = 0;
    virtual GLfloat getSize()=0;
    void setAlive(bool alive);
    bool isAlive();


private:
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;
    bool alive;

signals:

public slots:

};

#endif // ENGINEOBJECT_H
