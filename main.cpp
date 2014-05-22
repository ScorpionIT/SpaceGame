#include <QApplication>
#include <QVector>
#include <QTime>
#include <QDebug>

#include "gameminecrisis.h"
#include <QDebug>

int main(int argc,char** argv)
{
    QApplication game(argc,argv);

    GameMineCrisis* gameMineCrisis=new GameMineCrisis();
    gameMineCrisis->start();

    return game.exec();
}
