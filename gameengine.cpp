#include "gameengine.h"
#include <QDebug>

GameEngine::GameEngine(Camera *camera)
{
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

    objs = new QList<AbstractEngineObject*>;
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

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //createRandomCheckpoint();

    glClearColor (1.0, 1.0, 1.0, 0.0);
}

void GameEngine::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w/(GLfloat) h, 1, 800); //TODO
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GameEngine::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

    camera->render();

    glPushMatrix();

      for (QList<AbstractEngineObject*>::iterator i = objs->begin(); i != objs->end(); i++)
      {
          glTranslatef((*i)->getPositionX(), (*i)->getPositionY(), (*i)->getPositionZ());
          if ((*i)->hasTexture())
          {
              GLuint textureId = loadTexture ( (*i)->getTexturePath() );
              glBindTexture(GL_TEXTURE_2D, textureId);
          }
          (*i)->render();
      }

    glPopMatrix();

  glPopMatrix();

  swapBuffers();
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
  return textureId; //Returns the id of the texture
}



void GameEngine::addObject (AbstractEngineObject *obj)
{
  objs->append(obj);
}
