#include <QApplication>
#include <QVector>
#include <QTime>
#include <QDebug>

#include "gameengine.h"
#include "camera.h"
#include "sky.h"
#include "player.h"
#include "checkpoint.h"


void addRandomCheckpoints(GameEngine* gm,int numberOfCheckpoint);
bool isThereACheckpoint(GLdouble px,GLdouble py,GLdouble pz,QVector<Checkpoint*>& checkpoints);
int main(int argc,char** argv)
{
    QApplication game(argc,argv);
    const int NUMBER_OF_CHECKPOINT=20;

    Camera* camera = new Camera(0, -200, 0, 0, 0, 0);
    //Sky* sky = new Sky(NUMBER_OF_CHECKPOINT*Checkpoint::DISTANCE+Checkpoint::SIZE);
    Sky* sky = new Sky(100);
    GameEngine* gm = new GameEngine(camera,sky->getSize()*100);
    Player* player = new Player();

    gm->addObject(sky);
    gm->addObject(player);
    //addRandomCheckpoints(gm,NUMBER_OF_CHECKPOINT);
    gm->resize(800, 600);

    gm->show();
    gm->updateGL();

    return game.exec();
}


bool isThereACheckpoint(GLdouble px,GLdouble py,GLdouble pz,QVector<Checkpoint*>& checkpoints)
{
    for(int i=0;i<checkpoints.size();i++)
        if(px>=checkpoints[i]->getPositionX()-Checkpoint::SIZE/2 && px<=checkpoints[i]->getPositionX()+Checkpoint::SIZE/2 && py>=checkpoints[i]->getPositionY()-Checkpoint::SIZE/2 && py<=checkpoints[i]->getPositionY()+Checkpoint::SIZE/2 && pz>=checkpoints[i]->getPositionZ()-Checkpoint::SIZE/2 && pz<=checkpoints[i]->getPositionZ()+Checkpoint::SIZE/2 )
            return true;
    return false;
}

void addRandomCheckpoints(GameEngine* gm,int numberOfCheckpoint)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    QVector<Checkpoint*> checkpoints;
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
        }while(isThereACheckpoint(x,y,z,checkpoints));
        checkpoints.push_back(new Checkpoint(x,y,z));
        gm->addObject(checkpoints.back());
    }
    qDebug()<<"Exit from creation of random checkpoints"<<endl;
}


