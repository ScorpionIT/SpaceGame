#include "gameengine.h"
#include <QDebug>

GameEngine::GameEngine(Camera *camera, GLdouble viewVolume_):
    QGLWidget(QGLFormat(QGL::DoubleBuffer)), viewVolume(viewVolume_)
{
    //setFormat(QGL::DoubleBuffer | QGL::Rgba);
    this->camera = camera;

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

    objsToRenderAfterRenderCamera = new QList<EngineObject*>;
    objsToRenderBeforeRenderCamera = new QList<EngineObject*>;

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
    glPushMatrix();

    for (QList<EngineObject*>::iterator obj = objsToRenderBeforeRenderCamera->begin(); obj != objsToRenderBeforeRenderCamera->end(); obj++)
    {
        if((*obj)->isAlive())
        {
            if ((*obj)->hasTexture())
            {
                glEnable(GL_TEXTURE_2D);
                GLuint textureId = loadTexture ( (*obj)->getTexturePath() );
                glBindTexture(GL_TEXTURE_2D, textureId);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            glPushMatrix();
            (*obj)->render();
            glPopMatrix();
            if ((*obj)->hasTexture())
                glDisable (GL_TEXTURE_2D);
        }

    }
    glPopMatrix();
    camera->render();


    glPushMatrix();

    for (QList<EngineObject*>::iterator obj = objsToRenderAfterRenderCamera->begin(); obj != objsToRenderAfterRenderCamera->end(); obj++)
    {
        if((*obj)->isAlive())
        {
            if ((*obj)->hasTexture())
            {
                glEnable(GL_TEXTURE_2D);
                GLuint textureId = loadTexture ( (*obj)->getTexturePath() );
                glBindTexture(GL_TEXTURE_2D, textureId);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            glPushMatrix();
            (*obj)->render();
            glPopMatrix();
            if ((*obj)->hasTexture())
                glDisable (GL_TEXTURE_2D);
        }

    }

    glPopMatrix();


    swapBuffers();
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


GLuint GameEngine::loadTexture(QString imgPath)
{
    QImage im;
    im.load(imgPath);
    QImage image = QGLWidget::convertToGLFormat (im);
    if (image.isNull())
        qDebug() << "Impossibile caricare la texture " << imgPath << endl;
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGBA,                       //Format OpenGL uses for image
                 image.width(), image.height(),  //Width and height
                 0,                            //The border of the image
                 GL_RGBA, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image.bits());               //The actual pixel data
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.width() , image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    return textureId; //Returns the id of the texture*/
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
}


void GameEngine::addObjectToRenderBeforeRenderCamera(EngineObject *obj)
{
    objsToRenderBeforeRenderCamera->append(obj);
}

void GameEngine::addObjectToRenderAfterRenderCamera(EngineObject *obj)
{
    objsToRenderAfterRenderCamera->append(obj);
}
