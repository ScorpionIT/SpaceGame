#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "opengl.h"
#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QKeyEvent>

#include "camera.h"
#include "model.h"

typedef struct
{
    int w, h;
    uchar* img;
    int img_siz;
} texture;

class GameEngine: public QGLWidget
{
    Q_OBJECT

public:
    GameEngine(Camera* camera,GLdouble viewVolume);
    void setCamera (Camera* camera);

    void clean(); // Clean screen, call before each redraw

    void drawText (QString text, GLfloat x, GLfloat y, GLfloat z, QFont font=QFont());

    // OPENGL'S DRAWING BASE FUNCTIONS
    void pushMatrix();
    void popMatrix();
    void renderCamera();
    void Translate (GLfloat x, GLfloat y, GLfloat z);
    void Rotate (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void setColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

    // TEXTURE FUNCTIONS
    void enableTexture();
    void disableTexture();
    GLuint loadTexture(QString imgPath);
    void setTexture(GLuint textureId);

    // GEOMETRIC PRIMITIVES
    GLUquadric* sphereSettings (GLboolean textured, GLboolean wired);
    void drawSphere(GLUquadric* settings, GLfloat size, GLint slices, GLint stacks);
    void drawCube (GLfloat size);
    /*void drawCube(GLfloat size, GLuint textureId);
    void drawCube(GLfloat size, GLuint textureId_F, GLuint textureId_R, GLuint textureId_L,
                                   GLuint textureId_B, GLuint textureId_T, GLuint textureId_B);*/

    // MODEL FUNCTION
    //Model* loadModel (QString modelPath);
    void drawModel (Model*model);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);


private:
    int QloadModeltexture(obj_t *obj, char *filename, texture *tex);
    void glRenderObj(obj_t *obj);
    GLuint textures[OBJ_MAX_MATERIALS];

    Camera *camera;
    GLdouble viewVolume;
    GLfloat ambientLight[4];
    GLfloat specular[4];
    GLfloat specref[4];
    GLfloat lightPos0[4];
    GLfloat  spotDir0[3];

signals:
    void keyPress (QString key);
    void keyRelease (QString key);
};

#endif // GAMEENGINE_H
