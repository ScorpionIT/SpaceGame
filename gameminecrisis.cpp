#include "gameminecrisis.h"

GameMineCrisis::GameMineCrisis()
{
    camera = new Camera(0, -15, 5,1,-15,5);
    sky = new Sky(GameMineCrisis::NUMBER_OF_CHECKPOINTS*Checkpoint::DISTANCE+Checkpoint::SIZE);
    gm = new GameEngine(camera,sky->getSize()*100);
    player = new Player(camera,gm,sky);
    earth=new Earth(0,sky->getSize()*3,0,sky->getSize()) ;
    timerGame=10;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);
    numberOfcheckpoint=NUMBER_OF_CHECKPOINTS;
}

void GameMineCrisis::start()
{
    gm->addObjectToRenderAfterRenderCamera(earth);
    gm->addObjectToRenderBeforeRenderCamera(player);
    QObject::connect(gm, SIGNAL(keyPress(QString)),
                     player, SLOT(moveOn(QString)));
    QObject::connect(gm, SIGNAL(keyRelease(QString)),
                     player, SLOT(moveOff(QString)));
    addRandomMeteorites();
    addRandomCheckpoints();
    addRandomObstacles();
    gm->addObjectToRenderAfterRenderCamera(sky);
    gm->resize (800, 600);
    gm->show();
    gm->updateGL();
}

void GameMineCrisis::addRandomObstacles()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    obstacles.push_back(new Obstacle(100,20,40));
    gm->addObjectToRenderAfterRenderCamera(obstacles.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_OBSTACLES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2) +Obstacle::SIZE);
            y=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE);
            z=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE);
        }while(isThereAnObject(x,y,z,obstacles)!=-1 && isThereAnObject(x,y,z,checkpoints)!=-1);
        obstacles.push_back(new Obstacle(x,y,z));
        gm->addObjectToRenderAfterRenderCamera(obstacles.back());
    }
    qDebug()<<"Exit from creation of random meteorites"<<endl;

}



int GameMineCrisis::isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject)
{
    /*for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-engineObject[i]->getSize()/2 && x<=engineObject[i]->getPositionX()+engineObject[i]->getSize()/2 && y>=engineObject[i]->getPositionY()-engineObject[i]->getSize()/2 && y<=engineObject[i]->getPositionY()+engineObject[i]->getSize()/2 && z>=engineObject[i]->getPositionZ()-engineObject[i]->getSize()/2 && z<=engineObject[i]->getPositionZ()+engineObject[i]->getSize()/2 )
            return i;*/
    for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-(engineObject[i]->getSize()+15)/2 && x<=engineObject[i]->getPositionX()+(engineObject[i]->getSize()+15)/2 && y>=engineObject[i]->getPositionY()-(engineObject[i]->getSize()+15)/2 && y<=engineObject[i]->getPositionY()+(engineObject[i]->getSize()+15)/2 && z>=engineObject[i]->getPositionZ()-(engineObject[i]->getSize()+15)/2 && z<=engineObject[i]->getPositionZ()+(engineObject[i]->getSize()+15)/2 )
            return i;
    return -1;
}

void GameMineCrisis::addRandomCheckpoints()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(Checkpoint::DISTANCE,0,0,true));
        gm->addObjectToRenderAfterRenderCamera(checkpoints.back());
    }
    for(int i=0;i<GameMineCrisis::NUMBER_OF_CHECKPOINTS-1;i++)
    {
        GLint x,y,z;
        do
        {
            x=(checkpoints[checkpoints.size()-1]->getPositionX()+Checkpoint::DISTANCE)* (qrand()%2);
            y=(checkpoints[checkpoints.size()-1]->getPositionY()+Checkpoint::DISTANCE)* (qrand()%2);
            z=(checkpoints[checkpoints.size()-1]->getPositionZ()+Checkpoint::DISTANCE)* (qrand()%2);
        }while(isThereAnObject(x,y,z,checkpoints)!=-1);
        checkpoints.push_back(new Checkpoint(x,y,z,false));
        gm->addObjectToRenderAfterRenderCamera(checkpoints.back());
    }

    qDebug()<<"Exit from creation of random checkpoints"<<endl;
}

void GameMineCrisis::addRandomMeteorites()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    meteorites.push_back(new Meteorite(0,0,0));
    gm->addObjectToRenderAfterRenderCamera(meteorites.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_METEORITES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            y=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            z=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
        }while(isThereAnObject(x,y,z,meteorites)!=-1);
        meteorites.push_back(new Meteorite(x,y,z));
        gm->addObjectToRenderAfterRenderCamera(meteorites.back());
    }
    qDebug()<<"Exit from creation of random meteorites"<<endl;

}

void GameMineCrisis::gameOver()
{
    timer->stop();
    player->stop();
    sky->stop();

}

void GameMineCrisis::update()
{
    for(int i=0;i<meteorites.size();i++)
        if(dynamic_cast<Meteorite*>(meteorites[i])!=NULL)
        {
            Meteorite*meteorite=dynamic_cast<Meteorite*>(meteorites[i]);
            meteorite->hit(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20);
           // qDebug()<<meteorites[i]->getPositionX()<<"    "<<meteorites[i]->getPositionY()<<"   "<<meteorites[i]->getPositionZ()<<endl;
           //   qDebug()<<camera->getEyeX()+player->getShiftX()*20<<"     "<<camera->getEyeY()+player->getShiftY()*20<<"           "<<camera->getEyeZ()+player->getShiftZ()*20<<endl;
        }
    timerGame-=0.01;
    if(isThereAnObject(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20,meteorites)!=-1)
        gameOver();
    if(isThereAnObject(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20,obstacles)!=-1)
        gameOver();
    int indexOfObject=isThereAnObject(camera->getEyeX(),camera->getEyeY(),camera->getEyeZ(),checkpoints);
    if(indexOfObject!=-1)
    {
        checkpoints[indexOfObject]->setAlive(false);
        checkpoints.remove(indexOfObject);
        if(!checkpoints.empty())
        {
            Checkpoint* checkpoint=dynamic_cast<Checkpoint*>(checkpoints.front());
            if(checkpoint!=NULL)
                checkpoint->setActive(true);
        }
        timerGame+=Checkpoint::ADDITIONAL_TIME;
        numberOfcheckpoint--;
    }
    if(timerGame<0.1)
    {
        timerGame=0.0;
        gameOver();
    }
    qDebug()<<"timerGame  "<<timerGame<<endl;
    qDebug()<<"numberOfcheckpoint  "<<numberOfcheckpoint<<endl;
}


