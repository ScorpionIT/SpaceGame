#include "player.h"
#include <QDebug>

Player::Player(GameEngine* gm, Camera *camera, Sky* sky) :
    EngineObject (gm), MAX_SPEED(100), STANDARD_SPEED(50), MIN_SPEED(10)
{
    this->gm=gm;
    this->sky=sky;
    this->camera=camera;

    seeLeft=false;
    seeRight=false;
    seeUp=false;
    seeDown=false;
    moveUp=true;
    incrementShift=false;
    decrementShift=false;
    moveWhingRight=false;
    moveWhingUp=false;
    stopMove=false;
    shift = STANDARD_SPEED/10;
    rotateAngleXY = 3;
    rotateAngleXZ = 0.1;
    rotateXY = 0.0;
    rotateXZ = 0.0;
    rotateModelXZ = 0.0;
    whingAngle = 0.0;
    tailAngle = 0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    //setPosition(-2, -5, -20);
    //setPosition (camera->getEyeX(), camera->getEyeY(), camera->getEyeZ());
    gm->makeCurrent();
    model = new Model ("data/obj/f16/f16.obj");
    pause (false);
}

void Player::render()
{
    gm->pushMatrix();
    gm->enableTexture();
    //gm->Translate(getPositionX() ,getPositionY(), getPositionZ());
    gm->Translate(-2, -5, -10-shift);
    gm->Rotate(180,0,1,0);
    gm->Rotate(rotateModelXZ, 1, 0, 0);
    gm->Rotate(whingAngle,0,0,1);
    gm->Rotate(tailAngle,0,1,0);
    gm->drawModel(model);
    gm->disableTexture();
    gm->popMatrix();

}

GLfloat Player::getSize()
{
    return 0;
}

void Player::pause(bool p)
{
    if (p)
        timer->stop();
    else
        timer->start(25);
}

void Player::move()
{
    GLfloat px=camera->getEyeX();
    GLfloat py=camera->getEyeY();
    GLfloat pz=camera->getEyeZ();
    GLdouble pxNew=0,pyNew=0,pzNew=0;
    if(!stopMove)
    {
        if(incrementShift)
        {
            emit turboOn();
            if (shift*10 <= MAX_SPEED)
                shift+=0.1;
        }

        if(decrementShift)
        {
            if((shift)*10 >= MIN_SPEED)
                shift-=0.1;
            rotateAngleXY= 4;
        }

        if (!incrementShift)
        {
            if (shift*10 > STANDARD_SPEED)
                shift-= 0.1;
            emit turboOff();
        }
        if (!decrementShift)
            if (shift*10 < STANDARD_SPEED)
                shift+= 0.1;

        rotateAngleXY= 3;
    }
    if(moveUp)
    {
        pxNew=getShiftX()*shift;
        pyNew=getShiftY()*shift;
        pzNew=getShiftZ()*shift;
        if(isInsideSky(px+pxNew,py+pyNew,pz+pzNew))
        {
            px+=pxNew;
            py+=pyNew;
            pz+=pzNew;
            camera->setEye(px,py,pz);
            camera->setForward(camera->getForwardX()+pxNew,camera->getForwardY()+pyNew,camera->getForwardZ()+pzNew);
        }

    }
    if(seeUp && rotateXZ<=5)
    {
        if (rotateModelXZ-0.5 >= -10)
            rotateModelXZ -= 0.5;
        rotateXZ+=0.05;
        camera->setForward(camera->getForwardX(),camera->getForwardY(),rotateXZ+pz);
        //moveWhingUp=true;
    }

    if(seeDown && rotateXZ>=-5)
    {
        if (rotateModelXZ+0.5 <= 10)
            rotateModelXZ += 0.5;
        rotateXZ-=0.05;
        camera->setForward(camera->getForwardX(),camera->getForwardY(),rotateXZ+pz);
        //moveWhingUp=false;
    }

    if (!seeUp && !seeDown)
    {
        if (rotateModelXZ > 0)
            rotateModelXZ -= 0.5;
        else if (rotateModelXZ < 0)
            rotateModelXZ += 0.5;
    }

    if(seeRight)
    {
        if (tailAngle-0.5 >= -10.0)
            tailAngle -= 0.5;
        whingAngle += 1;
        if(whingAngle>=20)
            whingAngle=20;
        rotateXY-=rotateAngleXY;
        if(rotateXY%360==0 )
            rotateXY=0;
        camera->setForward(cos(rotateXY*M_PI/180)+px,sin(rotateXY*M_PI/180)+py,camera->getForwardZ());
        moveWhingRight=true;
    }
    else
    {
        if(moveWhingRight)
        {
            if (tailAngle+0.5 <= 0)
                tailAngle += 0.5;
            whingAngle -= 1;
            if(whingAngle<0)
                whingAngle=0;
        }
    }


    if(seeLeft)
    {
        if (tailAngle+0.5 <= 10)
            tailAngle += 0.5;
        whingAngle -= 1;
        if(whingAngle<=-20)
            whingAngle=-20;
        rotateXY+=rotateAngleXY;
        if(rotateXY%360==0 )
            rotateXY=0;
        camera->setForward(cos(rotateXY*M_PI/180)+px,sin(rotateXY*M_PI/180)+py,camera->getForwardZ());
        moveWhingRight=false;
    }
    else
    {
        if (tailAngle-0.5 >= 0)
            tailAngle -= 0.5;
        if(!moveWhingRight)
        {
            whingAngle += 1;
            if(whingAngle>=0)
                whingAngle=0;
        }
    }
    //setPosition(camera->getForwardX(),camera->getForwardY(),camera->getForwardZ()); ???
}

void Player::moveOn(QString key)
{
    if(key=="DOWN")
        seeUp=true;
    if(key == "UP")
        seeDown=true;
    if(key == "RIGHT")
        seeRight=true;
    if(key == "LEFT")
        seeLeft=true;
    if(key== "W")
        incrementShift=true;
    if(key== "S")
        decrementShift=true;
}

void Player::moveOff(QString key)
{
    if(key=="DOWN")
        seeUp=false;
    if(key == "UP")
        seeDown=false;
    if(key == "RIGHT")
        seeRight=false;
    if(key == "LEFT")
        seeLeft=false;
    if(key== "W")
        incrementShift=false;
    if(key== "S")
        decrementShift=false;
}

GLfloat Player::getShiftX()
{
    return cos(rotateXY*M_PI/180);
}


GLfloat Player::getShiftY()
{
    return sin(rotateXY*M_PI/180);
}

GLfloat Player::getShiftZ()
{
    return rotateXZ;
}

bool Player::isInsideSky(GLdouble px,GLdouble py,GLdouble pz)
{
    if(px>=sky->getPositionX()-sky->getSize()/2 && px<=sky->getPositionX()+sky->getSize()/2 && py>=sky->getPositionY()-sky->getSize()/2 && py<=sky->getPositionY()+sky->getSize()/2 && pz>=sky->getPositionZ()-sky->getSize()/2 && pz<=sky->getPositionZ()+sky->getSize()/2 )
        return true;
    return false;
}

