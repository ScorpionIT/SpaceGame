#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "opengl.h"
#include <QGLWidget>
#include <QString>
#include <QDebug>
#include <QOffscreenSurface>

#define approx 15 // COLLISION APPROXIMATION

struct ObjectSize
{
    GLfloat width;
    GLfloat height;
    GLfloat depth;

    ObjectSize()
    {
        this->width = 0;
        this->height = 0;
        this->depth = 0;
    }
};

class EngineObject : public QOffscreenSurface
{
    Q_OBJECT

public:
    EngineObject ();
    virtual GLfloat getPositionX();
    virtual GLfloat getPositionY();
    virtual GLfloat getPositionZ();
    virtual ObjectSize getSize();
    virtual void setSize (GLfloat width, GLfloat height, GLfloat depth);
    virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);
    virtual void render() = 0;
    static bool collision(EngineObject *obj, EngineObject *obj1);

protected:
    GLuint loadTexture(QString imgPath);

private:
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;
    ObjectSize size;

signals:

public slots:

};

#endif // ENGINEOBJECT_H
