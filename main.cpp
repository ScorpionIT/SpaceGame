#include <QApplication>
#include <QVector>
#include <QTime>
#include <QDebug>

#include "gameengine.h"
#include "camera.h"
#include "sky.h"
#include "player.h"

#include "gameminecrisis.h"
#include <QDebug>

int main(int argc,char** argv)
{
    QApplication game(argc,argv);

    Camera *camera = new Camera(0, -15, 0, 0, 0, 0);
    Sky *sky = new Sky(GameMineCrisis::NUMBER_OF_CHECKPOINT*Checkpoint::DISTANCE+Checkpoint::SIZE);
    GameEngine* gm = new GameEngine(camera,sky->getSize()*100);

    Player* player = new Player();

    gm->addObject (sky);
    gm->addObject (player);
    /*GameMineCrisis* gameMineCrisis=new GameMineCrisis(gm,sky);

    gameMineCrisis->addRandomCheckpoints();
    gameMineCrisis->addRandomMeteorites();*/

    gm->resize (800, 600);

    gm->show();
    gm->updateGL();

    return game.exec();
}
