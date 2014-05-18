#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include <QList>

#include <GL/glu.h>

#include "abstractengineobject.h"
#include "camera.h"

using namespace std;

class GameEngine: public QGLWidget
{
    Q_OBJECT;

public:

    GameEngine(Camera* camera);
    void setCamera (Camera* camera);
    GLuint loadTexture(QString imgPath);
    void addObject (AbstractEngineObject *obj);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void drawSky();
    void paintGL();

private:
    QList<AbstractEngineObject*> *objs;
    Camera *camera;
    GLfloat ambientLight[4];
    GLfloat specular[4];
    GLfloat specref[4];
    GLfloat lightPos0[4];
    GLfloat  spotDir0[3];

};

#endif // GAMEENGINE_H
