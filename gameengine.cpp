#include "gameengine.h"
#include <QDebug>

GameEngine::GameEngine()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
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

void GameEngine::paintGL()
{


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
          gluLookAt(px,py,pz,fx,fy,fz, 0.0, 0.0,1.0);

          glPushMatrix();

            for (QList<AbstractEngineObject*>::iterator i = objs->begin(); i != objs->end(); i++)
            {
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

void GameEngine::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) w/(GLfloat) h, 1,SKY_SIZE*100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GameEngine::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Up)
       seeUp=true;
    if(event->key()==Qt::Key_Down)
        seeDown=true;
    if(event->key()==Qt::Key_Right)
        seeRight=true;
    if(event->key()==Qt::Key_Left)
        seeLeft=true;

    if(event->key()==Qt::Key_W)
        incrementShift=true;
    if(event->key()==Qt::Key_S)
        decrementShift=true;


}


void GameEngine::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Up)
            seeUp=false;
    if(event->key()==Qt::Key_Down)
            seeDown=false;
    if(event->key()==Qt::Key_Right)
            seeRight=false;
    if(event->key()==Qt::Key_Left)
            seeLeft=false;

    if(event->key()==Qt::Key_W)
        incrementShift=false;
    if(event->key()==Qt::Key_S)
        decrementShift=false;
}

void GameEngine::move()
{

    GLdouble pxNew=0,pyNew=0,pzNew=0;
    if(incrementShift)
    {
        shift=shift+MIN_SPEED;
        if(shift>MAX_SPEED)
            shift=MAX_SPEED;
    }

    if(decrementShift)
    {
        shift=shift-MIN_SPEED;
        if(shift<MIN_SPEED)
            shift=MIN_SPEED;
    }
    if(moveUp)
    {
        GLdouble cosen=cos(rotateXY*M_PI/180);
        GLdouble sen=sin(rotateXY*M_PI/180);
        pxNew=shift*cosen;
        pyNew=shift*sen;
        pzNew=rotateXZ*shift;
        if(/*!collision(-4+fx+pxNew*32,-10+fy+pyNew*32,-20+fz+pzNew*32) && insideSky(px+pxNew,py+pyNew,pz+pzNew)*/ true)
        {
            px+=pxNew;
            py+=pyNew;
            pz+=pzNew;
            fx=fx+shift*cosen;
            fy=fy+shift*sen;
            fz=fz+pzNew;
        }
        if(/*collisionCheckpoint(px,py,pz)*/true)
        {
            playerTimer+=TIME_CHECKPOINT;
        }

    }
    if(seeUp && rotateXZ<=5)
    {
        rotateXZ+=0.05;
        fz=rotateXZ+ pz;
    }
    if(seeDown && rotateXZ>=-5)
    {
        rotateXZ-=0.05;
        fz=rotateXZ+pz;

    }
    if(seeRight)
    {
        whingAngle++;
        if(whingAngle>=10)
            whingAngle=10;
        rotateXY-=3;
        if(rotateXY%360==0 )
            rotateXY=0;
        fx=cos(rotateXY*M_PI/180)+px;
        fy=sin(rotateXY*M_PI/180)+py;
        moveWhingRight=true;
    }
    else
    {
        if(moveWhingRight)
        {
            whingAngle--;
            if(whingAngle<0)
                whingAngle=0;
        }
    }

    if(seeLeft)
    {
        whingAngle--;
        if(whingAngle<=-10)
            whingAngle=-10;
        rotateXY+=3;
        if(rotateXY%360==0 )
            rotateXY=0;
        fx=cos(rotateXY*M_PI/180)+px;
        fy=sin(rotateXY*M_PI/180)+py;
        moveWhingRight=false;
    }
    else
    {
        if(!moveWhingRight)
        {
            whingAngle++;
            if(whingAngle>=0)
                whingAngle=0;
        }
    }

    // Refresh the Window
    updateGL();
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
