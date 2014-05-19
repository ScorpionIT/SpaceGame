#include <QApplication>
#include <QVector>
#include <QTime>
#include "gameengine.h"
#include "camera.h"
#include "sky.h"
#include "gameminecrisis.h"
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
    GameMineCrisis* gameMineCrisis=new GameMineCrisis(gm,sky);
    gameMineCrisis->addRandomCheckpoints(NUMBER_OF_CHECKPOINT);
    gameMineCrisis->addRandomMeteorites(NUMBER_OF_METEORITE);
    gm->resize (800, 600);
    gm->show();

    return game.exec();
}
