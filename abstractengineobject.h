#ifndef ABSTRACTENGINEOBJECT_H
#define ABSTRACTENGINEOBJECT_H

#include <QObject>
#include <GL/gl.h>

class AbstractEngineObject : public QObject
{
    Q_OBJECT
public:
    AbstractEngineObject(GLfloat x=0,GLfloat y=0,GLfloat z=0);
    virtual bool hasTexture();
    virtual QString getTexturePath();
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
