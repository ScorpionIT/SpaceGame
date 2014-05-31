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

void GameEngine::clean()
{
    makeCurrent();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
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
        if (isFullScreen())
            showNormal();
        else
            showFullScreen();

    if(event->key()==Qt::Key_P)
        emit keyRelease("P");
}

void GameEngine::drawText (QString text, QFont font)
{
    drawText (text, this->width()/2, this->height()/2, true, font);
}

void GameEngine::drawText (QString text, GLfloat x, GLfloat y, bool center, QFont font)
{
    int chSize; //Dimensione carattere
    if (center)
        chSize = font.weight()/2;
    else
        chSize = 0;

    this->renderText (x- ( chSize * (text.length()/2) ), y + chSize, text, font);

}

// OPENGL'S DRAWING BASE FUNCTIONS
void GameEngine::pushMatrix()
{
    makeCurrent();
    glPushMatrix();
}

void GameEngine::popMatrix()
{
    makeCurrent();
    glPopMatrix();
}

void GameEngine::renderCamera()
{
    makeCurrent();
    gluLookAt(camera->getEyeX(), camera->getEyeY(), camera->getEyeZ(),
              camera->getForwardX(), camera->getForwardY(), camera->getForwardZ(), 0.0, 0.0, 1.0);
}

void GameEngine::Translate (GLfloat x, GLfloat y, GLfloat z)
{
    makeCurrent();
    glTranslatef(x, y, z);
}
void GameEngine::Rotate (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    makeCurrent();
    glRotatef (angle, x, y, z);
}

void GameEngine::setColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    makeCurrent();
    glColor4f(red, green, blue, alpha);
}

void GameEngine::clearColor ()
{
    makeCurrent();
    glClear(GL_COLOR);
}


// GEOMETRIC PRIMITIVES
GLUquadric* GameEngine::sphereSettings (GLboolean textured, GLboolean wired)
{
    GLUquadric *quad = gluNewQuadric();
    if (textured)
        gluQuadricTexture(quad,1);
    if (wired)
        gluQuadricDrawStyle(quad, GLU_LINE);
    return quad;
}

void GameEngine::drawSphere(GLUquadric* settings, GLfloat size, GLint slices, GLint stacks)
{
    makeCurrent();
    gluSphere(settings, size, slices, stacks);
}

void GameEngine::drawCube (GLfloat size)
{
    makeCurrent();
    glBegin(GL_QUADS);
    // Front Face
    glVertex3f(size,size,size);

    glVertex3f(size,-size,size);

    glVertex3f(-size,-size,size);

    glVertex3f(-size,size,size);


    // Back Face
    glVertex3f(size,size,-size);

    glVertex3f(size,-size,-size);

    glVertex3f(-size,-size,-size);

    glVertex3f(-size,size,-size);

    // Top Face
    glVertex3f(size,size,-size);

    glVertex3f(size,size,size);

    glVertex3f(-size,size,size);

    glVertex3f(-size,size,-size);

    // Bottom Face
    glVertex3f(size,-size,-size);

    glVertex3f(size,-size,size);

    glVertex3f(-size,-size,size);

    glVertex3f(-size,-size,-size);

    // Left face
    glVertex3f(size,size,size);

    glVertex3f(size,size,-size);

    glVertex3f(size,-size,-size);

    glVertex3f(size,-size,size);

    // Right face
    glVertex3f(-size,size,size);

    glVertex3f(-size,size,-size);

    glVertex3f(-size,-size,-size);

    glVertex3f(-size,-size,size);
    glEnd();
}

// MODEL FUNCTION
//Model* GameEngine::loadModel (QString modelPath);
void GameEngine::drawModel (Model* model)
{
    makeCurrent();
    glRenderObj (model->getModel());
}

// TEXTURE FUNCITONS
void GameEngine::enableTexture()
{
    makeCurrent();
    glEnable(GL_TEXTURE_2D);
}

void GameEngine::disableTexture()
{
    makeCurrent();
    glDisable(GL_TEXTURE_2D);
}

GLuint GameEngine::loadTexture(QString imgPath)
{
    makeCurrent();
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

void GameEngine::setTexture(GLuint textureId)
{
    makeCurrent();
    glBindTexture(GL_TEXTURE_2D, textureId);
}

// MODEL PRIVATE FUNCIOTN
int GameEngine::QloadModeltexture(obj_t *obj, char *filename, texture *tex)
{
    char FullName[512];
    tex = (texture*) malloc(sizeof(texture));
    if(tex == NULL)
    {
        if(libobj_verbose)
            fprintf(stderr, "libobj: Error: couldn't alloc memory for new texture\n");
        return -1;
    }
    memset( tex, 0, sizeof(texture));         // zero out the new texture

    // open the image
    if(obj->dir != NULL)
        sprintf(FullName, "%s%s", obj->dir, filename);
    else
        strcpy(FullName, filename);

    QImage im;
    im.load(FullName);
    QImage image = QGLWidget::convertToGLFormat (im);
    if (image.isNull())
        fprintf (stderr, "Impossibile caricare la texture %s", FullName);
    tex->w = image.width();
    tex->h = image.height();
    //fprintf (stderr, "Carico la Texture in memeria");
    tex->img = (uint8_t*) malloc(image.byteCount());
    memcpy (tex->img, image.bits(), image.byteCount());
    //tex->img = image.bits();
    //fprintf (stderr, "...OK\n");
    return true;
}

void GameEngine::glRenderObj(obj_t *obj)
{
    makeCurrent();
    texture tex;
    int i, j, k;

    for(i = 0; i < obj->materials_n; i++ )
    {
        tex.w = 1;
        tex.h = 1;
        tex.img = (uint8_t*) malloc(4);
        tex.img_siz = 1;
        if(obj->materials[i]->diffuse_tex != NULL)
        {
            if( QloadModeltexture(obj, obj->materials[i]->diffuse_tex, &tex) )
                goto no_texture;
        }
        else
        {
no_texture:
            tex.img[0] = (uint8_t)(255 * obj->materials[i]->diffuse.r);
            tex.img[1] = (uint8_t)(255 * obj->materials[i]->diffuse.g);
            tex.img[2] = (uint8_t)(255 * obj->materials[i]->diffuse.b);
            tex.img[3] = (uint8_t)(255 * obj->materials[i]->alpha);
            glColor4f( 1, 1, 1, 1);
        }
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        //qDebug() << textures[i] << endl;
        //        fprintf (stderr, "Carico la Texture");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.w, tex.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.img);
        //        fprintf (stderr, "...OK\n");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        for(j = 0; j < obj->materials[i]->polygons_n; j++)
        {
            objpolygon *poly = obj->materials[i]->polygons[j];
            for(k = 1; k+1 < poly->points_n; k++)
            {
                glBegin(GL_TRIANGLES); // could be moved outside of loop?
#define p1	poly->points[0]
#define p2	poly->points[k]
#define p3	poly->points[k+1]
                if(p1.texcoord != -1)
                    glTexCoord2f( obj->texcoords[p1.texcoord].u, obj->texcoords[p1.texcoord].v );
                if(p1.normal != -1)
                    glNormal3f( obj->normals[p1.normal].a, obj->normals[p1.normal].b, obj->normals[p1.normal].c );
                glVertex3f( obj->verts[p1.vertex].x, obj->verts[p1.vertex].y, obj->verts[p1.vertex].z );

                if(p2.texcoord != -1)
                    glTexCoord2f( obj->texcoords[p2.texcoord].u, obj->texcoords[p2.texcoord].v );
                if(p2.normal != -1)
                    glNormal3f( obj->normals[p2.normal].a, obj->normals[p2.normal].b, obj->normals[p2.normal].c );
                glVertex3f( obj->verts[p2.vertex].x, obj->verts[p2.vertex].y, obj->verts[p2.vertex].z );

                if(p3.texcoord != -1)
                    glTexCoord2f( obj->texcoords[p3.texcoord].u, obj->texcoords[p3.texcoord].v );
                if(p3.normal != -1)
                    glNormal3f( obj->normals[p3.normal].a, obj->normals[p3.normal].b, obj->normals[p3.normal].c );
                glVertex3f( obj->verts[p3.vertex].x, obj->verts[p3.vertex].y, obj->verts[p3.vertex].z );
#undef p1
#undef p2
#undef p3
                glEnd(); //could be moved outside of loop?
            }
        }
        //free(tex.img);//this safe?
    }
}
