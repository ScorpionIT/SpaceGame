#include "earth.h"

Earth::Earth(GLfloat x,GLfloat y, GLfloat z, GLfloat size)
{
    setPosition(x, y, z);
    setSize(size, size, size);
    this->size=size;
    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);

    quad = gluNewQuadric();
    gluQuadricTexture(this->quad, GLU_TRUE);

    textureId = this->loadTexture("data/texture/earth.png");
}

void Earth::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(getPositionX(),getPositionY(),getPositionZ());

    glColor4f(1.0,1.0,1.0,1.0);
    glRotatef(rotationAngle,0,0,1);
    gluSphere(quad,this->size, 50, 50);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void Earth::stop()
{
    timer->stop();
}

void Earth::rotate()
{
    rotationAngle+=0.3;
}

