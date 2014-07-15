#include <QApplication>
#include <QMainWindow>
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>

#include "gameminecrisis.h"
#include <QDebug>

int main(int argc,char** argv)
{
    QApplication app (argc,argv);

    GameMineCrisis* gameMineCrisis=new GameMineCrisis();
    gameMineCrisis->start();

    return app.exec();
}
