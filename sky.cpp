#include "sky.h"

Sky::Sky(GLfloat size_)
{
    quad = gluNewQuadric();
    setPosition(0, 0, 0);
    this->size=size_;
    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);
}

bool Sky::hasTexture()
{
    return true;
}

QString Sky::getTexturePath()
{
    return QString ("data/texture/sky.png");
}

void Sky::render()
{
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    gluQuadricTexture(this->quad, true);
    glColor4f(1.0,1.0,1.0,1.0);
    glRotatef(rotationAngle,0,0,1);
    gluSphere(this->quad, this->size, 100, 100);

}

GLfloat Sky::getSize()
{
    return size;
}

void Sky::stop()
{
    timer->stop();
}

void Sky::rotate()
{
    rotationAngle+=0.6;
}
