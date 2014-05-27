#include "earth.h"

Earth::Earth(GameEngine* gm, GLfloat x,GLfloat y, GLfloat z, GLfloat size) :
    EngineObject(gm)
{
    setPosition(x, y, z);
    this->size=size;
    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);
    textureId = this->gm->loadTexture("data/texture/earth.png");
}

void Earth::render()
{
    gm->pushMatrix();
    gm->enableTexture();
    gm->setTexture(textureId);
    gm->Translate(getPositionX(),getPositionY(),getPositionZ());
    //gm->Translate(0,0,0);
    gm->setColor(1.0,1.0,1.0,1.0);
    gm->Rotate(rotationAngle,0,0,1);
    gm->drawSphere(gm->sphereSettings(true,false),this->size, 50, 50);
    gm->disableTexture();
    gm->popMatrix();

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

