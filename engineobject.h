#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "opengl.h"
#include <QObject>
#include "gameengine.h"


class EngineObject : public QObject
{
    Q_OBJECT

public:
    EngineObject (GameEngine* gm);
    virtual GLfloat getPositionX();
    virtual GLfloat getPositionY();
    virtual GLfloat getPositionZ();
    virtual void setPosition (GLfloat x, GLfloat y, GLfloat z);
    virtual void render() = 0;
    virtual GLfloat getSize()=0;

protected:
    GameEngine *gm;

private:
    GLfloat positionX;
    GLfloat positionY;
    GLfloat positionZ;

signals:

public slots:

};

#endif // ENGINEOBJECT_H
