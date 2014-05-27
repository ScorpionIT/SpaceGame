#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "engineobject.h"

class Obstacle : public EngineObject
{
    Q_OBJECT

public:
    Obstacle(GameEngine *gm, GLfloat x, GLfloat y, GLfloat z);
    static const GLfloat SIZE=20;
    void render();
    GLfloat getSize();
};


#endif // OBSTACLE_H
