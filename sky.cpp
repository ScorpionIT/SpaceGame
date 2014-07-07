#include "sky.h"

Sky::Sky(GLfloat size)
{
    setPosition(0, 0, 0);
    setSize (size, size, size);

    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);

    this->quad = gluNewQuadric();
    gluQuadricTexture(this->quad, GLU_TRUE);

    this->textureId = loadTexture("data/texture/starmap.png");
}

void Sky::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glRotatef(rotationAngle,0,0,1);
    gluSphere(quad, getSize().width*3, 10, 10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Sky::stop()
{
    timer->stop();
}

void Sky::rotate()
{
    rotationAngle+=0.3;
}

