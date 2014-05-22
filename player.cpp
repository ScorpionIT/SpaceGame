#include "player.h"
#include <QDebug>

Player::Player(Camera *camera_,GameEngine* gm_):MAX_SPEED(10),MIN_SPEED(1)
{
    gm=gm_;
    model = new ModelLoader ("data/objs/f16.obj");
    camera=camera_;
    seeLeft=false;
    seeRight=false;
    seeUp=false;
    seeDown=false;
    moveUp=true;
    incrementShift=false;
    decrementShift=false;
    moveWhingRight=false;
    shift = 1;
    rotateXY = 0.0;
    rotateXZ = 0.0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
    //setPosition(camera->getEyeX(),camera->getEyeY(),camera->getEyeZ());
    //setPosition(0,0,0);
}

bool Player::hasTexture()
{
    return false;
}

QString Player::getTexturePath()
{
    //return QString ("data/model/snail/snail_tex_red.png");
    return QString ("data/model/MP5K/Tex_0004_1.bmp");
}

void Player::render()
{
    glTranslatef(-2,-5,-20);
    glRotatef(180,0,1,0);
    //glScaled();
    model->renderModel();
}

GLfloat Player::getSize()
{
    return 0;
}


void Player::move()
{
    GLfloat px=camera->getEyeX();
    GLfloat py=camera->getEyeY();
    GLfloat pz=camera->getEyeZ();
    GLdouble pxNew=0,pyNew=0,pzNew=0;
    if(incrementShift)
    {
        shift=shift+1;
    }

    if(decrementShift)
    {
        shift=shift-1;
        if(shift<MIN_SPEED)
            shift=MIN_SPEED;
    }
    if(moveUp)
    {
        GLdouble cosen=cos(rotateXY*M_PI/180);
        GLdouble sen=sin(rotateXY*M_PI/180);
        pxNew=shift*cosen;
        pyNew=shift*sen;
        pzNew=rotateXZ*shift;
        /*if(!collision(px+pxNew*3,py+pyNew*3,pz+pzNew*3))
        {
            if(insideSky(px+pxNew,py+pyNew,pz+pzNew))
            {*/
        px+=pxNew;
        py+=pyNew;
        pz+=pzNew;
        camera->setEye(px,py,pz);
        camera->setForward(camera->getForwardX()+pxNew,camera->getForwardY()+pyNew,camera->getForwardZ()+pzNew);
        /*}
        }
        else
            gameOver=true;
        if(collisionCheckpoint(px,py,pz))
        {
            playerTimer+=TIME_CHECKPOINT;
        }*/

    }
    if(seeUp && rotateXZ<=5)
    {
        rotateXZ+=0.05;
        camera->setForward(camera->getForwardX(),camera->getForwardY(),rotateXZ+pz);
    }
    if(seeDown && rotateXZ>=-5)
    {
        rotateXZ-=0.05;
        camera->setForward(camera->getForwardX(),camera->getForwardY(),rotateXZ+pz);

    }
    if(seeRight)
    {
        /*whingAngle++;
        if(whingAngle>=10)
            whingAngle=10;*/
        rotateXY-=3;
        if(rotateXY%360==0 )
            rotateXY=0;
        camera->setForward(cos(rotateXY*M_PI/180)+px,sin(rotateXY*M_PI/180)+py,camera->getForwardZ());
        // moveWhingRight=true;
    }
    else
    {
        /*if(moveWhingRight)
        {
            whingAngle--;
            if(whingAngle<0)
                whingAngle=0;
        }*/
    }


    if(seeLeft)
    {
        /* whingAngle--;
        if(whingAngle<=-10)
            whingAngle=-10;*/
        rotateXY+=3;
        if(rotateXY%360==0 )
            rotateXY=0;
        camera->setForward(cos(rotateXY*M_PI/180)+px,sin(rotateXY*M_PI/180)+py,camera->getForwardZ());
        moveWhingRight=false;
    }
    else
    {
        if(!moveWhingRight)
        {
            /*   whingAngle++;
            if(whingAngle>=0)
                whingAngle=0;*/
        }
    }
    setPosition(camera->getEyeX(),camera->getEyeY(),camera->getEyeZ());
    gm->updateGL();
    qDebug()<<camera->getEyeX()<<"   "<<camera->getEyeY()<<"    "<<camera->getEyeZ()<<endl;
}

void Player::moveOn(QString key)
{
    if(key=="DOWN")
        seeDown=true;
    if(key == "UP")
        seeUp=true;
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
        seeDown=false;
    if(key == "UP")
        seeUp=false;
    if(key == "RIGHT")
        seeRight=false;
    if(key == "LEFT")
        seeLeft=false;
    if(key== "W")
        incrementShift=false;
    if(key== "S")
        decrementShift=false;
}

