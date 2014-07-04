#include "gameengine.h"
#include <QDebug>

GameEngine::GameEngine(Camera *camera, GLdouble viewVolume_):
    QGLWidget(QGLFormat(QGL::DoubleBuffer)), viewVolume(viewVolume_)
{
    //setFormat(QGL::DoubleBuffer | QGL::Rgba);
    this->camera = camera;

    this->objects = new QList<EngineObject*>();
    this->objectsBeforeCamera = new QList<EngineObject*>();

    ambientLight[0] = 0.5;
    ambientLight[1] = 0.5;
    ambientLight[2] = 0.5;
    ambientLight[3] = 1.0;

    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 0.0;
    specular[3] = 1.0;

    specref[0] = 1.0;
    specref[1] = 1.0;
    specref[2] = 1.0;
    specref[3] = 1.0;

    lightPos0[0] = 0.0;
    lightPos0[1] = 0.0;
    lightPos0[2] = 15000.0;
    lightPos0[3] = 1.0;

    spotDir0[0] = 0.0;
    spotDir0[1] = 0.0;
    spotDir0[2] = -0.0;

    hms = new HudMessageSystem(this);

    makeCurrent();
}

void GameEngine::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,ambientLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
    //	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,30.0f);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT, GL_SHININESS,1);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor (0.0, 0.0, 0.0, 0.0);
}

void GameEngine::paintGL()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    for (QList<EngineObject*>::iterator obj = objectsBeforeCamera->begin(); obj != objectsBeforeCamera->end(); obj++)
    {
        (*obj)->render();
    }

    camera->render();

    for (QList<EngineObject*>::iterator obj = objects->begin(); obj != objects->end(); obj++)
    {
        (*obj)->render();
    }

    for (QMap<QString, HudString*>::iterator hud = hms->getHudStrings()->begin(); hud != hms->getHudStrings()->end(); hud++)
    {
        //qDebug() << (*hud)->hud;
        qglColor((*hud)->color);
        renderText((*hud)->x, (*hud)->y, (*hud)->hud, (*hud)->font);
    }
    glFlush();
}

void GameEngine::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w/(GLfloat) h, 1, viewVolume);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GameEngine::setCamera (Camera* camera)
{
    this->camera = camera;
}

HudMessageSystem *GameEngine::getHms()
{
    return hms;
}

void GameEngine::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Up)
        emit keyPress ("UP");
    if(event->key()==Qt::Key_Down)
        emit keyPress ("DOWN");
    if(event->key()==Qt::Key_Right)
        emit keyPress ("RIGHT");
    if(event->key()==Qt::Key_Left)
        emit keyPress ("LEFT");

    if(event->key()==Qt::Key_W)
        emit keyPress ("W");
    if(event->key()==Qt::Key_S)
        emit keyPress ("S");
}

void GameEngine::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Up)
        emit keyRelease ("UP");

    if(event->key()==Qt::Key_Down)
        emit keyRelease ("DOWN");

    if(event->key()==Qt::Key_Right)
        emit keyRelease ("RIGHT");

    if(event->key()==Qt::Key_Left)
        emit keyRelease ("LEFT");

    if(event->key()==Qt::Key_W)
        emit keyRelease ("W");

    if(event->key()==Qt::Key_S)
        emit keyRelease ("S");

    if(event->key()==Qt::Key_F)
    {
        if (isFullScreen())
            showNormal();
        else
            showFullScreen();
    }

    if(event->key()==Qt::Key_P)
        emit keyRelease("P");
    else if(event->key()==Qt::Key_R)
        emit keyRelease("R");
}

void GameEngine::addObject (EngineObject* obj, bool beforeCamera)
{
    if (beforeCamera)
        objectsBeforeCamera->append(obj);
    else
        objects->append(obj);
}

void GameEngine::removeObject(EngineObject *obj, bool beforeCamera)
{
    if (beforeCamera)
        objectsBeforeCamera->removeOne(obj);
    else
        objects->removeOne(obj);
}

void GameEngine::cleanObject()
{
    objectsBeforeCamera->clear();
    objects->clear();
}
