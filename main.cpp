#include <QApplication>
#include <QVector>
#include <QTime>
#include "gameengine.h"
#include "camera.h"
#include "sky.h"
#include "checkpoint.h"
#include "meteorite.h"
#include <QDebug>

void addRandomCheckpoints(GameEngine* gm,int numberOfCheckpoint);
bool isThereAnObject(GLdouble px,GLdouble py,GLdouble pz,QVector<AbstractEngineObject*>& checkpoints);
void addRandomMeteorites(GameEngine* gm,int numberOfMeteorite,Sky* sky);
int main(int argc,char** argv)
{
    QApplication game(argc,argv);
    const int NUMBER_OF_CHECKPOINT=20;
    const int NUMBER_OF_METEORITE=100;

    Camera *camera = new Camera(0, -15, 0, 0, 0, 0);
    Sky *sky = new Sky(NUMBER_OF_CHECKPOINT*Checkpoint::DISTANCE+Checkpoint::SIZE);
    GameEngine* gm = new GameEngine(camera,sky->getSize()*100);
    gm->addObject (sky);
    addRandomCheckpoints(gm,NUMBER_OF_CHECKPOINT);
    addRandomMeteorites(gm,NUMBER_OF_METEORITE,sky);
    gm->resize (800, 600);
    gm->show();

    return game.exec();
}


bool isThereAnObject(GLdouble px,GLdouble py,GLdouble pz,QVector<AbstractEngineObject*>& engineObject)
{
    for(int i=0;i<engineObject.size();i++)
        if(px>=engineObject[i]->getPositionX()-engineObject[i]->getSize()/2 && px<=engineObject[i]->getPositionX()+engineObject[i]->getSize()/2 && py>=engineObject[i]->getPositionY()-engineObject[i]->getSize()/2 && py<=engineObject[i]->getPositionY()+engineObject[i]->getSize()/2 && pz>=engineObject[i]->getPositionZ()-engineObject[i]->getSize()/2 && pz<=engineObject[i]->getPositionZ()+engineObject[i]->getSize()/2 )
            return true;
    return false;
}

void addRandomCheckpoints(GameEngine* gm,int numberOfCheckpoint)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    QVector<AbstractEngineObject*> checkpoints;
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(0,0,Checkpoint::DISTANCE));
        gm->addObject(checkpoints.back());
    }
    for(int i=0;i<numberOfCheckpoint-1;i++)
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

void addRandomMeteorites(GameEngine* gm,int numberOfMeteorite,Sky* sky)
{
    QVector<AbstractEngineObject*> meteorites;
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    meteorites.push_back(new Meteorite(0,0,0));
    gm->addObject(meteorites.back());
    while(numberOfMeteorite>=0)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            y=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            z=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
        }while(isThereAnObject(x,y,z,meteorites));
        meteorites.push_back(new Meteorite(x,y,z));
        gm->addObject(meteorites.back());
        numberOfMeteorite--;
    }
    qDebug()<<"Exit from creation of random meteorites"<<endl;

}


