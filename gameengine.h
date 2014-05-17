#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <QTimer>
#include <QKeyEvent>
#include <QGLWidget>
#include <GL/glut.h>
#include <QGLBuilder>
 #include <Qt>
#include <iostream>
#include<cmath>
#include"imageloader.h"
using namespace std;

class GameEngine: public QGLWidget
{
    Q_OBJECT;



public:

    GameEngine();

    struct Actor{
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLint size;
    };

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

    GLuint textureId[1]; //The id of the textur
    GLUquadric *quad;
    Image* image;

    GLfloat rotateSky=0;
    Actor sky;
    GLuint loadTexture(Image* image)
    {
       GLuint textureId;
       glGenTextures(1, &textureId); //Make room for our texture
       glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
       //Map the image to the texture
       glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 image->pixels);               //The actual pixel data
       return textureId; //Returns the id of the texture
    }
    float playerTimer=10;


protected:
    void initializeGL();

    void resizeGL(int w, int h);
    void drawSky();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
public slots:
    void move();
    void paintGL();



};

#endif // GAMEENGINE_H
