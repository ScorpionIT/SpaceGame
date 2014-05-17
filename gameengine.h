#ifndef GAMEENGINE_H
#define GAMEENGINE_H



#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include <QList>

#include <GL/glut.h>

//#include <iostream>
#include<cmath>

#include "abstractengineobject.h"

using namespace std;

class GameEngine: public QGLWidget
{
    Q_OBJECT;

public:

    GameEngine();
    GLuint loadTexture(QString imgPath);
    void addObject (AbstractEngineObject *obj);

private:
    QList<AbstractEngineObject*> *objs;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void drawSky();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void paintGL();

public slots:
    void move();


public:
    GLint time_value=25;
    GLint time_value_of_timer=100;

    int whingAngle=0;
    bool moveWhingRight=false;

    GLfloat  shift = 1;
    GLint   rotateXY = 0.0;
    GLfloat   rotateXZ = 0.0;

    //The first triplet of coordinates of vector camera's
    GLdouble px=0;
    GLdouble py=-15;
    GLdouble pz=5;


    //The last triplet of coordinates of vector camera's
    GLdouble fx=cos(rotateXY*M_PI/180)+px;
    GLdouble fy=sin(rotateXY*M_PI/180)+py;
    GLdouble fz=rotateXZ+pz;

    //GLMmodel* f16 ;


    GLfloat  ambientLight[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat  specular[4]		= { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat  specref[4]		= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat	 lightPos0[4]		= { 0.0f, 0.0f, 15000.0f, 1.0f };
    GLfloat  spotDir0[3]		= { 0.0f,0.0f,-1.0f };

    bool seeLeft=false;
    bool seeRight=false;
    bool seeUp=false;
    bool seeDown=false;
    bool moveUp=true;
    bool incrementShift=false;
    bool decrementShift=false;

    const GLfloat MAX_SPEED=10;
    const GLfloat MIN_SPEED=1;

    //vector<Actor> obstacles;


    //vector<Actor> checkpoints;
    const int SIZE_CHECKPOINT=200;
    const int DISTANCE_CHECKPOINT=SIZE_CHECKPOINT*10;
    const int TIME_CHECKPOINT=10;
    const int NUMBER_CHECKPOINT=20;
    const int SKY_SIZE=NUMBER_CHECKPOINT*DISTANCE_CHECKPOINT+SIZE_CHECKPOINT;


    GLfloat rotateSky=0;
    float playerTimer=10;
};

#endif // GAMEENGINE_H
