
#include <QApplication>
#include "gameengine.h"
#include "sky.h"

int main(int argc,char** argv)
{
    QApplication game(argc,argv);

    GameEngine* gm = new GameEngine();
    Sky *sky = new Sky();

    gm->addObject (sky);
    gm->resize (800, 600);
    gm->show();

    return game.exec();
}

