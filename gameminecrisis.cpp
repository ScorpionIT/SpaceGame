#include "gameminecrisis.h"

GameMineCrisis::GameMineCrisis(GameEngine* gm_,Sky* sky_)
{
    gm=gm_;
    sky=sky_;
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
    QVector<EngineObject*> checkpoints;
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(0,0,Checkpoint::DISTANCE));
        gm->addObject(checkpoints.back());
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
        gm->addObject(checkpoints.back());
    }
    qDebug()<<"Exit from creation of random checkpoints"<<endl;
}

void GameMineCrisis::addRandomMeteorites()
{
    QVector<EngineObject*> meteorites;
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    meteorites.push_back(new Meteorite(0,0,0));
    gm->addObject(meteorites.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_METEORITE;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            y=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            z=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
        }while(isThereAnObject(x,y,z,meteorites));
        meteorites.push_back(new Meteorite(x,y,z));
        gm->addObject(meteorites.back());
    }
    qDebug()<<"Exit from creation of random meteorites"<<endl;

}
