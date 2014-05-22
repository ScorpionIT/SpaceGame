#include "gameminecrisis.h"

GameMineCrisis::GameMineCrisis()
{
    camera = new Camera(0, -15, 5,1,-15,+5);
    sky = new Sky(GameMineCrisis::NUMBER_OF_CHECKPOINT*Checkpoint::DISTANCE+Checkpoint::SIZE);
    gm = new GameEngine(camera,sky->getSize()*100);
    player = new Player(camera,gm);
}

void GameMineCrisis::start()
{
    gm->addObjectToRenderBeforeRenderCamera(player);
    QObject::connect(gm, SIGNAL(keyPress(QString)),
                     player, SLOT(moveOn(QString)));
    QObject::connect(gm, SIGNAL(keyRelease(QString)),
                     player, SLOT(moveOff(QString)));
    //addRandomMeteorites();
    //addRandomCheckpoints();
    gm->addObjectToRenderAfterRenderCamera(sky);
    gm->resize (800, 600);
    gm->show();
    gm->updateGL();
}



bool GameMineCrisis::isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject)
{
    for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-engineObject[i]->getSize()/2 && x<=engineObject[i]->getPositionX()+engineObject[i]->getSize()/2 && y>=engineObject[i]->getPositionY()-engineObject[i]->getSize()/2 && y<=engineObject[i]->getPositionY()+engineObject[i]->getSize()/2 && z>=engineObject[i]->getPositionZ()-engineObject[i]->getSize()/2 && z<=engineObject[i]->getPositionZ()+engineObject[i]->getSize()/2 )
            return true;
    return false;
}

void GameMineCrisis::addRandomCheckpoints()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(0,0,Checkpoint::DISTANCE));
        gm->addObjectToRenderAfterRenderCamera(checkpoints.back());
    }
    for(int i=0;i<GameMineCrisis::NUMBER_OF_CHECKPOINT-1;i++)
    {
        GLint x,y,z;
        do
        {
            x=(checkpoints[checkpoints.size()-1]->getPositionX()+Checkpoint::DISTANCE)* (qrand()%2);
            y=(checkpoints[checkpoints.size()-1]->getPositionY()+Checkpoint::DISTANCE)* (qrand()%2);
            z=(checkpoints[checkpoints.size()-1]->getPositionZ()+Checkpoint::DISTANCE)* (qrand()%2);
        }while(isThereAnObject(x,y,z,checkpoints));
        checkpoints.push_back(new Checkpoint(x,y,z));
        qDebug()<<x<<y<<z<<endl;
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
    for(int i=0;i<GameMineCrisis::NUMBER_OF_METEORITE;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            y=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            z=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
        }while(isThereAnObject(x,y,z,meteorites));
        meteorites.push_back(new Meteorite(x,y,z));
        gm->addObjectToRenderAfterRenderCamera(meteorites.back());
    }
    qDebug()<<"Exit from creation of random meteorites"<<endl;

}

void GameMineCrisis::moveMeteorites()
{
    for(int i=0;i<meteorites.size();i++)
        if(dynamic_cast<Meteorite*>(meteorites[i])!=NULL)
            dynamic_cast<Meteorite*>(meteorites[i])->move(player->getPositionX(),player->getPositionY(),player->getPositionZ());
}


