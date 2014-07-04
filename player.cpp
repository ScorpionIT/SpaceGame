#include "player.h"
#include <QDebug>

Player::Player(Camera *camera, Sky* sky) :
    MAX_SPEED(100), STANDARD_SPEED(50), MIN_SPEED(10)
{
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
    whingAngleStep = 2;
    whingMaxAngle = 30;
    tailAngle = 0.0;
    tailAngleStep = 2;
    tailMaxAngle = 20.0;

    model = new Model();
    model->loadModel("data/obj/Wraith Raider Starship/Wraith Raider Starship.obj");
    model->scaleModel(0.08);
    model->calcDim();
    modelDepth = model->getDim().depth-shift*10+MIN_SPEED*2;
    modelList = model->getGlList();

    int dist = (shift*10)*2-MIN_SPEED*2;
    GLfloat pX = (-camera->getEyeX()+camera->getForwardX())*dist+camera->getEyeX();
    GLfloat pY = (-camera->getEyeY()+camera->getForwardY())*dist+camera->getEyeY();
    GLfloat pZ = (-camera->getEyeZ()+camera->getForwardZ())*dist+camera->getEyeZ();

    setPosition (pX, pY, pZ);
    setSize (model->getDim().width, model->getDim().height, model->getDim().depth);
}

void Player::reset()
{
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
}

void Player::render()
{
    glPushMatrix();
    glTranslatef(0, -15, -modelDepth-shift*10);

    glRotatef(180,0,1,0);
    glRotatef(rotateModelXZ, 1, 0, 0);
    glRotatef(whingAngle,0,0,1);
    glRotatef(tailAngle,0,1,0);

    glCallList(modelList);

    glPopMatrix();

}

void Player::update()
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
        if (tailAngle-tailAngleStep >= -tailMaxAngle)
            tailAngle -= tailAngleStep;
        whingAngle += whingAngleStep;
        if(whingAngle>=whingMaxAngle)
            whingAngle=whingMaxAngle;
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
            if (tailAngle+tailAngleStep <= 0)
                tailAngle += tailAngleStep;
            whingAngle -= whingAngleStep;
            if(whingAngle<0)
                whingAngle=0;
        }
    }


    if(seeLeft)
    {
        if (tailAngle+tailAngleStep <= tailMaxAngle)
            tailAngle += tailAngleStep;

        whingAngle -= whingAngleStep;
        if(whingAngle<=-whingMaxAngle)
            whingAngle=-whingMaxAngle;

        rotateXY+=rotateAngleXY;
        if(rotateXY%360==0 )
            rotateXY=0;
        camera->setForward(cos(rotateXY*M_PI/180)+px,sin(rotateXY*M_PI/180)+py,camera->getForwardZ());
        moveWhingRight=false;
    }
    else
    {
        if (tailAngle-tailAngleStep >= 0)
            tailAngle -= tailAngleStep;
        if(!moveWhingRight)
        {
            whingAngle += whingAngleStep;
            if(whingAngle>=0)
                whingAngle=0;
        }
    }

    int dist = (shift*10)*2-MIN_SPEED*2;
    GLfloat pX = (-camera->getEyeX()+camera->getForwardX())*dist+camera->getEyeX();
    GLfloat pY = (-camera->getEyeY()+camera->getForwardY())*dist+camera->getEyeY();
    GLfloat pZ = (-camera->getEyeZ()+camera->getForwardZ())*dist+camera->getEyeZ();

    setPosition (pX, pY, pZ);
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
    if(px>=sky->getPositionX()-sky->getSize().width/2 && px<=sky->getPositionX()+sky->getSize().width/2 && py>=sky->getPositionY()-sky->getSize().width/2 && py<=sky->getPositionY()+sky->getSize().width/2 && pz>=sky->getPositionZ()-sky->getSize().width/2 && pz<=sky->getPositionZ()+sky->getSize().width/2 )
        return true;
    return false;
}

