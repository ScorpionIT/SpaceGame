#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include <QObject>
#include <GL/gl.h>

class EngineObject : public QObject
{
    Q_OBJECT
public:
    EngineObject(GLfloat x=0,GLfloat y=0,GLfloat z=0);
    virtual bool hasTexture();
    virtual QString getTexturePath();
    virtual GLfloat getPositionX();
    virtual GLfloat getPositionY();
    virtual GLfloat getPositionZ();
    virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);
    virtual void render() = 0;

private:
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;

signals:

public slots:

};

#endif // ENGINEOBJECT_H
