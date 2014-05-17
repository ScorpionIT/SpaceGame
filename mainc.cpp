
#include <QApplication>
#include "gameengine.h"

int main(int argc,char** argv)
{
    QApplication game(argc,argv);

    GameEngine gm;

    gm.resize (800, 600);
    gm.show();

    return game.exec();
}

