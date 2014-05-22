#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "opengl.h"
#include <QGLWidget>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include <QList>
#include <QKeyEvent>

#include "engineobject.h"
#include "camera.h"

using namespace std;

class GameEngine: public QGLWidget
{
    Q_OBJECT
signals:
  void keyPress (QString key);
  void keyRelease (QString key);
public:

    GameEngine(Camera* camera,GLdouble viewVolume);
    void setCamera (Camera* camera);
    GLuint loadTexture(QString imgPath);
    void addObjectToRenderAfterRenderCamera (EngineObject *obj);
    void addObjectToRenderBeforeRenderCamera (EngineObject *obj);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);


private:
    QList<EngineObject*> *objsToRenderAfterRenderCamera;
    QList<EngineObject*> *objsToRenderBeforeRenderCamera;
    Camera *camera;
    GLdouble viewVolume;
    GLfloat ambientLight[4];
    GLfloat specular[4];
    GLfloat specref[4];
    GLfloat lightPos0[4];
    GLfloat  spotDir0[3];
};

#endif // GAMEENGINE_H
