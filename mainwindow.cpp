#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    label = new QLabel();
    QImage splash(":/data/splash.png");
    label->setPixmap (QPixmap::fromImage(splash));

    startGame = new QPushButton ("Start Game");
    quitGame = new QPushButton ("Close Game");
    connect (startGame, SIGNAL(clicked()), this, SLOT (launchGame()));
    connect (quitGame, SIGNAL(clicked()), qApp, SLOT (quit()));
    vLayout = new QVBoxLayout();
    vLayout->addWidget(label);
    vLayout->addWidget(startGame);
    vLayout->addWidget(quitGame);
    setLayout(vLayout);

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->adjustSize();
    this->move(QApplication::desktop()->screenGeometry().center() - this->rect().center());
}

void MainWindow::launchGame()
{
    delete startGame;
    delete quitGame;
    progress = new QProgressBar();

    vLayout->addWidget(progress);
}

