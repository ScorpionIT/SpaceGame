#include "gameminecrisis.h"

GameMineCrisis::GameMineCrisis()
{
    camera = new Camera(0, 0, 0, 1, 0, 0);
    GLfloat skySize = GameMineCrisis::NUMBER_OF_CHECKPOINTS*Checkpoint::DISTANCE+Checkpoint::SIZE;
    gm = new GameEngine(camera,skySize*100);
    sky = new Sky(skySize);
    player = new Player(camera, sky);
    earth=new Earth(0, sky->getSize().width*3, 0, sky->getSize().width);


    int id = QFontDatabase::addApplicationFont("data/fonts/DIGITALDREAMNARROW.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    textFont.setFamily(family);
    textFont.setBold(true);

    timer_gameMainLoop = new QTimer(this);
    connect(timer_gameMainLoop, SIGNAL(timeout()), this, SLOT(gameMainLoop()));
    uTimer = new QTimer(this);
    connect(uTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    QDir dataDir ("data");

    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/background.ogg"));
    backgroundMusic->setVolume(75);
    backgroundMusic->play();

    checkpointEffect = new QMediaPlayer();
    checkpointEffect->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/checkpoint.ogg"));
    checkpointEffect->setVolume(100);

    turboEffect = new QMediaPlayer();
    turboEffect->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/turbo.ogg"));
    turboEffect->setVolume(100);


    gameOverEffect = new QMediaPlayer();
    gameOverEffect->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/gameover.ogg"));
    gameOverEffect->setVolume(100);

    this->hms = gm->getHms();
}

void GameMineCrisis::start(bool connect)
{
    this->gameover = false;
    this->win = false;
    numberOfcheckpoint=NUMBER_OF_CHECKPOINTS;
    pause = false;
    timerGameT = QTime(0, 0, 40, 0);

    if (connect)
    {
        QObject::connect(gm, SIGNAL(keyPress(QString)), player, SLOT(moveOn(QString)));
        QObject::connect(gm, SIGNAL(keyRelease(QString)), player, SLOT(moveOff(QString)));
        QObject::connect(gm, SIGNAL(keyRelease(QString)), this, SLOT(processKeys(QString)));
        QObject::connect (player, SIGNAL(turboOn()), turboEffect, SLOT(play()));
        QObject::connect (player, SIGNAL(turboOff()), turboEffect, SLOT(stop()));
        QObject::connect (backgroundMusic, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(loopBackgroundMusic(QMediaPlayer::MediaStatus))); //LOOP BACKGROUND MUSIC
    }

    addRandomMeteorites();
    addRandomCheckpoints();
    addRandomObstacles();

    gm->addObject(sky, false);
    gm->addObject(earth, false);
    gm->addObject(player, true);
    if (!gm->isVisible())
    {
        gm->resize (1024, 768);
        gm->show();
    }
    gm->showFullScreen();
    if (!timer_gameMainLoop->isActive())
        timer_gameMainLoop->start(1);
    startTime = QTime::currentTime();
    if (!uTimer->isActive())
        uTimer->start(1);
}

void GameMineCrisis::restart()
{
    timer_gameMainLoop->stop();
    camera->setEye(0, 0, 0);
    camera->setForward(1, 0, 0);
    player->reset();
    gm->cleanObject();
    if (pause)
        this->processKeys("P");
    if (gameover)
    {
        this->gameover = false;
        hms->removeText("GAMEOVER");
    }
    if (win)
    {
        this->win = false;
        hms->removeText("WIN");
    }
    meteorites.clear();
    checkpoints.clear();
    obstacles.clear();
    backgroundMusic->play();
    start(false);
}

void GameMineCrisis::gameMainLoop()
{
    if (!gameover && !win && !pause)
    {
        this->update();
        player->update();
        hms->removeText("RESTART");
    }
    else
    {
        if (turboEffect->state() == QMediaPlayer::PlayingState)
            turboEffect->stop();
        textFont.setPixelSize(30);
        hms->setText("RESTART", QString ("PRESS R TO RESTART GAME"), gm->width()/2, gm->height()/2+70, true, textFont, Qt::green);
    }

    if (gameover)
    {
        textFont.setPixelSize(80);
        hms->setText("GAMEOVER", QString ("GAME OVER"), textFont, Qt::green);
    }
    else if (win)
    {
        textFont.setPixelSize(80);
        hms->setText("WIN", QString ("YOU WON"), textFont, Qt::green);
    }
    else if (pause)
    {
        textFont.setPixelSize(80);
        hms->setText("PAUSE", QString ("PAUSE"), textFont,Qt::green);
    }

    textFont.setPixelSize(20);
    hms->setText("Checkpoint", hud_checkpoints, 5, 45, false, textFont, Qt::green);
    hms->setText("timerGame", hud_timerGame, 5, 20, false, textFont, Qt::green);
    gm->updateGL();
}


void GameMineCrisis::addRandomObstacles()
{
    //qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    obstacles.push_back(new Obstacle(100,20,40));
    gm->addObject(obstacles.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_OBSTACLES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize().width/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize().width/2) +Obstacle::SIZE);
            y=(qrand() % ((int)sky->getSize().width/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize().width/2)+Obstacle::SIZE);
            z=(qrand() % ((int)sky->getSize().width/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize().width/2)+Obstacle::SIZE);
        }while(isThereAnObject(x,y,z,obstacles)!=-1 && isThereAnObject(x,y,z,checkpoints)!=-1);
        obstacles.push_back(new Obstacle(x,y,z));
        gm->addObject(obstacles.back());
    }
    //qDebug()<<"Exit from creation of random meteorites"<<endl;

}

int GameMineCrisis::isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject)
{
    for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-(engineObject[i]->getSize().width+15)/2 && x<=engineObject[i]->getPositionX()+(engineObject[i]->getSize().width+15)/2 && y>=engineObject[i]->getPositionY()-(engineObject[i]->getSize().width+15)/2 && y<=engineObject[i]->getPositionY()+(engineObject[i]->getSize().width+15)/2 && z>=engineObject[i]->getPositionZ()-(engineObject[i]->getSize().width+15)/2 && z<=engineObject[i]->getPositionZ()+(engineObject[i]->getSize().width+15)/2 )
            return i;
    return -1;
}

void GameMineCrisis::addRandomCheckpoints()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(Checkpoint::DISTANCE,0,0,true));

        gm->addObject(checkpoints.back());
    }
    for(int i=0;i<GameMineCrisis::NUMBER_OF_CHECKPOINTS-1;i++)
    {
        GLint x,y,z;
        do
        {
            x=(checkpoints[checkpoints.size()-1]->getPositionX()+Checkpoint::DISTANCE)* (qrand()%2);
            y=(checkpoints[checkpoints.size()-1]->getPositionY()+Checkpoint::DISTANCE)* (qrand()%2);
            z=(checkpoints[checkpoints.size()-1]->getPositionZ()+Checkpoint::DISTANCE)* (qrand()%2);
        }while(isThereAnObject(x,y,z,checkpoints)!=-1);
        checkpoints.push_back(new Checkpoint(x,y,z,false));
        gm->addObject(checkpoints.back());
    }
    //qDebug()<<"Exit from creation of random checkpoints"<<endl;
}

void GameMineCrisis::addRandomMeteorites()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    meteorites.push_back(new Meteorite(0,0,0));
    gm->addObject(meteorites.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_METEORITES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize().width/2))-(qrand() % ((int)sky->getSize().width/2));
            y=(qrand() % ((int)sky->getSize().width/2))-(qrand() % ((int)sky->getSize().width/2));
            z=(qrand() % ((int)sky->getSize().width/2))-(qrand() % ((int)sky->getSize().width/2));
        }while(isThereAnObject(x,y,z,meteorites)!=-1);
        meteorites.push_back(new Meteorite(x,y,z));
        gm->addObject(meteorites.back());
    }
    //qDebug()<<"Exit from creation of random meteorites"<<endl;

}

void GameMineCrisis::gameOver()
{
    uTimer->stop();
    //sky->stop();
    this->gameover = true;
    backgroundMusic->stop();
    gameOverEffect->play();
}

void GameMineCrisis::update()
{
    for(int i=0;i<meteorites.size();i++)
        if(dynamic_cast<Meteorite*>(meteorites[i])!=NULL)
        {
            Meteorite*meteorite=dynamic_cast<Meteorite*>(meteorites[i]);
            meteorite->hit(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20);
        }

    // COLLISIONI
    for(int i=0; i< meteorites.size(); i++)
    {
        if (EngineObject::collision (player, meteorites[i]))
            gameOver();
    }
    for(int i=0; i<obstacles.size(); i++)
    {
        if (EngineObject::collision (player, obstacles[i]))
            gameOver();
    }
    for(int i=0; i<checkpoints.size(); i++)
    {
        if (EngineObject::collision (player, checkpoints[i]) && dynamic_cast<Checkpoint*>(checkpoints[i])->isActive())
        {

            checkpointEffect->play();
            gm->removeObject(checkpoints[i]); //Aggiorno grafica
            checkpoints.remove(i); //Aggiorno logica
            if(!checkpoints.empty())
            {
                Checkpoint* checkpoint=dynamic_cast<Checkpoint*>(checkpoints.front());
                if(checkpoint!=NULL)
                    checkpoint->setActive(true);
            }
            timerGameT = timerGameT.addSecs(Checkpoint::ADDITIONAL_TIME);
            numberOfcheckpoint--;
        }
    }
    // COLLISIONI

    if (numberOfcheckpoint == 0)
        this->win = true;
    hud_checkpoints.clear();
    hud_checkpoints.append("Checkpoints: ");
    hud_checkpoints.append (QString::number(numberOfcheckpoint));

}

void GameMineCrisis::processKeys(QString key)
{
    if (key == "P")
    {
        if (!gameover)
        {
            if (pause)
            {
                QObject::connect(gm, SIGNAL(keyPress(QString)), player, SLOT(moveOn(QString)));
                startTime = QTime::currentTime();
                startTime = startTime.addSecs(-(timerGameT.second()-timerGame.second()));
                startTime = startTime.addMSecs(-(timerGameT.msec()-timerGame.msec()));
                uTimer->start(1);
                backgroundMusic->play();
                pause = false;
                hms->removeText("PAUSE");
            }
            else
            {
                QObject::disconnect(gm, SIGNAL(keyPress(QString)), player, SLOT(moveOn(QString)));
                uTimer->stop();
                backgroundMusic->pause();
                pause = true;
            }
        }
    }
    else if (key == "R")
    {
        if (gameover || win || pause)
            restart();
    }
}


void GameMineCrisis::loopBackgroundMusic(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
        backgroundMusic->play();
}

void GameMineCrisis::updateTimer()
{
    QTime current = QTime::currentTime();
    timerGame = timerGameT.addMSecs(current.msecsTo(startTime));
    if(timerGame.minute()==0 && timerGame.second() == 0)
    {
        timerGame.setHMS(0, 0, 0, 0);
        gameOver();
    }
    hud_timerGame.clear();
    hud_timerGame.append("Timer: ");
    hud_timerGame.append (timerGame.toString("mm:ss:zzz"));
}

