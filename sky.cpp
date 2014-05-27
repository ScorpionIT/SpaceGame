#include "sky.h"

Sky::Sky(GameEngine *gm, GLfloat size_) :
    EngineObject (gm)
{
    setPosition(0, 0, 0);
    this->size=size_;
    rotationAngle=0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer->start(25);
    //gm->makeCurrent();
    this->textureId = this->gm->loadTexture("data/texture/starmap.png");
}

void Sky::render()
{
    gm->pushMatrix();
    gm->enableTexture();
    gm->Translate(getPositionX(),getPositionY(),getPositionZ());
    gm->setColor(1.0, 1.0, 1.0, 1.0);
    gm->Rotate (rotationAngle,0,0,1);
    gm->setTexture(textureId);
    gm->drawSphere(gm->sphereSettings(true,false), this->size*3, 10, 10);
    gm->disableTexture();
    gm->popMatrix();
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
    rotationAngle+=0.3;
}
