#include "engineobject.h"

EngineObject::EngineObject()
{
}

GLfloat EngineObject::getPositionX()
{
    return this->positionX;
}

GLfloat EngineObject::getPositionY()
{
    return this->positionY;
}

GLfloat EngineObject::getPositionZ()
{
    return this->positionZ;
}

ObjectSize EngineObject::getSize()
{
    return this->size;
}

void EngineObject::setSize(GLfloat width, GLfloat height, GLfloat depth)
{
    this->size.width = width;
    this->size.height = height;
    this->size.depth = depth;
}

void EngineObject::setPosition (GLfloat x, GLfloat y, GLfloat z)
{
    this->positionX = x;
    this->positionY = y;
    this->positionZ = z;
}

GLuint EngineObject::loadTexture(QString imgPath)
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
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.width() , image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    return textureId; //Returns the id of the texture
}

bool EngineObject::collision(EngineObject* obj, EngineObject* obj1)
{
    if ( ( (obj->getPositionY()-obj->getSize().width+approx > obj1->getPositionY()-obj1->getSize().width &&
            obj->getPositionY()-obj->getSize().width+approx < obj1->getPositionY()+obj1->getSize().width)
            || (obj->getPositionY()+obj->getSize().width-approx > obj1->getPositionY()-obj1->getSize().width &&
                obj->getPositionY()+obj->getSize().width-approx < obj1->getPositionY()+obj1->getSize().width)) &&
         ( (obj->getPositionZ()-obj->getSize().height+approx > obj1->getPositionZ()-obj1->getSize().height &&
                     obj->getPositionZ()-obj->getSize().height+approx < obj1->getPositionZ()+obj1->getSize().height)
                     || (obj->getPositionZ()+obj->getSize().height-approx > obj1->getPositionZ()-obj1->getSize().height &&
                         obj->getPositionZ()+obj->getSize().height-approx < obj1->getPositionZ()+obj1->getSize().height)) &&
         ( (obj->getPositionX()-obj->getSize().depth+approx > obj1->getPositionX()-obj1->getSize().depth &&
                     obj->getPositionX()-obj->getSize().depth+approx < obj1->getPositionX()+obj1->getSize().depth)
                     || (obj->getPositionX()+obj->getSize().depth-approx > obj1->getPositionX()-obj1->getSize().depth &&
                         obj->getPositionX()+obj->getSize().depth-approx < obj1->getPositionX()+obj1->getSize().depth)) )
        return true;

    return false;
}
