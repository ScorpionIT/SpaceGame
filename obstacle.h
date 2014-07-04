#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "engineobject.h"

class Obstacle : public EngineObject
{
    Q_OBJECT

public:
    Obstacle(GLfloat x, GLfloat y, GLfloat z);
    static const GLfloat SIZE=20;
    void render();
};


#endif // OBSTACLE_H
