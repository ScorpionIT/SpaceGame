
#include <QApplication>
#include "gameengine.h"
#include "camera.h"
#include "sky.h"

int main(int argc,char** argv)
{
    QApplication game(argc,argv);

    Camera *camera = new Camera(0, -15, 0, 0, 0, 0);
    GameEngine* gm = new GameEngine(camera);
    Sky *sky = new Sky();

    gm->addObject (sky);
    gm->resize (800, 600);
    gm->show();

    return game.exec();
}

