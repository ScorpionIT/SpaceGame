#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "opengl.h"
#include <QGLWidget>
#include <QKeyEvent>
#include <QKeyEvent>
#include <QList>

#include "camera.h"
#include "engineobject.h"
#include "hudmessagesystem.h"

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
    GameEngine(Camera* camera, GLdouble viewVolume);
    void setCamera (Camera* camera);
    HudMessageSystem* getHms ();
    void addObject (EngineObject *obj, bool beforeCamera = false);
    void removeObject(EngineObject *obj, bool beforeCamera = false);
    void cleanObject();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    HudMessageSystem* hms;
    QList<EngineObject*> *objects;
    QList<EngineObject*> *objectsBeforeCamera;
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
