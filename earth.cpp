#include "earth.h"

Earth::Earth(GLfloat x,GLfloat y,GLfloat z,GLfloat size_)
{
    quad = gluNewQuadric();
    setPosition(x, y, z);
    this->size=size_;
    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);
}

bool Earth::hasTexture()
{
    return true;
}

QString Earth::getTexturePath()
{
    return QString ("data/texture/earth.png");
}

void Earth::render()
{
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    gluQuadricTexture(this->quad, true);
    glColor4f(1.0,1.0,1.0,1.0);
    glRotatef(rotationAngle,0,0,1);
    gluSphere(this->quad, this->size*2, 50, 50);

}

GLfloat Earth::getSize()
{
    return size;
}

void Earth::stop()
{
    timer->stop();
}

void Earth::rotate()
{
    rotationAngle+=0.3;
}
