#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include <QList>
#include <GL/glu.h>

#include "glm/glm.h"
#include "engineobject.h"
#include "camera.h"

using namespace std;

class GameEngine: public QGLWidget
{
    Q_OBJECT

public:

    GameEngine(Camera* camera,GLdouble viewVolume);
    void setCamera (Camera* camera);
    GLuint loadTexture(QString imgPath);
    void addObject (EngineObject *obj);
    static GLMmodel* loadModel (const char* modelPath);
    static void renderModel (GLMmodel* model);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QList<EngineObject*> *objs;
    Camera *camera;
    GLdouble viewVolume;
    GLfloat ambientLight[4];
    GLfloat specular[4];
    GLfloat specref[4];
    GLfloat lightPos0[4];
    GLfloat  spotDir0[3];

    GLMmodel* model;
    int displayList;

};

#endif // GAMEENGINE_H
