#include <QApplication>
#include <QMainWindow>
#include <QSplashScreen>
#include <QPixmap>
#include <QDebug>

#include "mainwindow.h"
#include "gameminecrisis.h"
#include <QDebug>

int main(int argc,char** argv)
{
    //QGL::setPreferredPaintEngine(QPaintEngine::OpenGL) ;
    QApplication app (argc,argv);

    /*QPixmap pixmap(":/data/splash.png");
    QSplashScreen splash (pixmap);
    splash.show();
    QCoreApplication::processEvents();*/

    GameMineCrisis* gameMineCrisis=new GameMineCrisis();
    gameMineCrisis->start();

    //splash.finish(dynamic_cast<QWidget*>(gameMineCrisis));

    /*QMainWindow window;
    window.show();*/
    //splash.finish(gameMineCrisis);

    /*MainWindow game;
    game.show();*/

    return app.exec();
}
