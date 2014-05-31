#include "gameminecrisis.h"

GameMineCrisis::GameMineCrisis()
{
    this->gameover = false;
    camera = new Camera(0, 0, 0, 1, 0, 0);
    GLfloat skySize = GameMineCrisis::NUMBER_OF_CHECKPOINTS*Checkpoint::DISTANCE+Checkpoint::SIZE;
    //GLfloat skySize = 1000;
    gm = new GameEngine(camera,skySize*100);
    sky = new Sky(gm, skySize);
    player = new Player(gm, camera, sky);
    earth=new Earth(gm, 0, sky->getSize()*3, 0, sky->getSize());
    //earth=new Earth(gm, 0,0,0,100) ;
    timerGame=10;

    timer_gameMainLoop = new QTimer(this);
    connect(timer_gameMainLoop, SIGNAL(timeout()), this, SLOT(gameMainLoop()));

    numberOfcheckpoint=NUMBER_OF_CHECKPOINTS;

    int id = QFontDatabase::addApplicationFont("data/fonts/DIGITALDREAMNARROW.ttf");
    //  qDebug() << id << endl;
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    textFont.setFamily(family);
    textFont.setBold(true);

    QDir dataDir ("data");

    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/background.ogg"));
    backgroundMusic->setVolume(75);

    checkpointEffect = new QMediaPlayer();
    checkpointEffect->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/checkpoint.ogg"));
    checkpointEffect->setVolume(100);

    turboEffect = new QMediaPlayer();
    turboEffect->setMedia(QUrl::fromLocalFile(dataDir.absolutePath()+"/audio/turbo.ogg"));
    turboEffect->setVolume(100);

}

void GameMineCrisis::start()
{
    QObject::connect(gm, SIGNAL(keyPress(QString)), player, SLOT(moveOn(QString)));
    QObject::connect(gm, SIGNAL(keyRelease(QString)), player, SLOT(moveOff(QString)));
    QObject::connect (player, SIGNAL(turboOn()), turboEffect, SLOT(play()));
    QObject::connect (player, SIGNAL(turboOff()), turboEffect, SLOT(stop()));
    QObject::connect (player, SIGNAL(turboOff()), turboEffect, SLOT());
    QObject::connect (backgroundMusic, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(loopBackgroundMusic(QMediaPlayer::MediaStatus))); //LOOP BACKGROUND MUSIC
    QObject::connect (turboEffect, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(loopTurboEffect(QMediaPlayer::MediaStatus))); //LOOP SOUND TURBO EFFECT

    addRandomMeteorites();
    addRandomCheckpoints();
    addRandomObstacles();
    //gm->addObjectToRenderAfterRenderCamera(sky);
    gm->resize (800, 600);
    gm->show();
    backgroundMusic->play();
    if (!timer_gameMainLoop->isActive())
        timer_gameMainLoop->start(1);

}

void GameMineCrisis::gameMainLoop()
{
    gm->clean();

    gm->pushMatrix();
    player->render();
    gm->popMatrix();

    gm->renderCamera();

    gm->pushMatrix();
    for (QVector<EngineObject*>::iterator obj = meteorites.begin(); obj != meteorites.end(); obj++)
    {
        //if((*obj)->isAlive())
        (*obj)->render();
    }

    for (QVector<EngineObject*>::iterator obj = checkpoints.begin(); obj != checkpoints.end(); obj++)
    {
        //if((*obj)->isAlive())
        (*obj)->render();
    }

    for (QVector<EngineObject*>::iterator obj = obstacles.begin(); obj != obstacles.end(); obj++)
    {
        //if((*obj)->isAlive())
        (*obj)->render();
    }

    earth->render();
    sky->render();
    gm->popMatrix();

    if (!gameover)
        this->update();
    else
    {
        gm->setColor(1.0, 0, 0, 1);
        textFont.setPixelSize(40);
        gm->drawText(QString ("GAME OVER"), textFont);
        //gm->clearColor();
    }

    //HUD
    gm->setColor(1.0, 0, 0, 1);
    textFont.setPixelSize(20);
    gm->drawText(hud_timerGame, 5, 20, false, textFont);
    gm->drawText(hud_checkpoints, 5, 45, false, textFont);
    gm->swapBuffers(); //Swap screen/buffer
}


void GameMineCrisis::addRandomObstacles()
{
    //qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    obstacles.push_back(new Obstacle(gm, 100,20,40));
    //gm->addObjectToRenderAfterRenderCamera(obstacles.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_OBSTACLES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2) +Obstacle::SIZE);
            y=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE);
            z=(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE)-(qrand() % ((int)sky->getSize()/2)+Obstacle::SIZE);
        }while(isThereAnObject(x,y,z,obstacles)!=-1 && isThereAnObject(x,y,z,checkpoints)!=-1);
        obstacles.push_back(new Obstacle(gm, x,y,z));
        //gm->addObjectToRenderAfterRenderCamera(obstacles.back());
    }
    //qDebug()<<"Exit from creation of random meteorites"<<endl;

}



int GameMineCrisis::isThereAnObject(GLdouble x, GLdouble y, GLdouble z, QVector<EngineObject *> &engineObject)
{
    /*for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-engineObject[i]->getSize()/2 && x<=engineObject[i]->getPositionX()+engineObject[i]->getSize()/2 && y>=engineObject[i]->getPositionY()-engineObject[i]->getSize()/2 && y<=engineObject[i]->getPositionY()+engineObject[i]->getSize()/2 && z>=engineObject[i]->getPositionZ()-engineObject[i]->getSize()/2 && z<=engineObject[i]->getPositionZ()+engineObject[i]->getSize()/2 )
            return i;*/
    for(int i=0;i<engineObject.size();i++)
        if(x>=engineObject[i]->getPositionX()-(engineObject[i]->getSize()+15)/2 && x<=engineObject[i]->getPositionX()+(engineObject[i]->getSize()+15)/2 && y>=engineObject[i]->getPositionY()-(engineObject[i]->getSize()+15)/2 && y<=engineObject[i]->getPositionY()+(engineObject[i]->getSize()+15)/2 && z>=engineObject[i]->getPositionZ()-(engineObject[i]->getSize()+15)/2 && z<=engineObject[i]->getPositionZ()+(engineObject[i]->getSize()+15)/2 )
            return i;
    return -1;
}

void GameMineCrisis::addRandomCheckpoints()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    if(checkpoints.empty())
    {
        checkpoints.push_back(new Checkpoint(gm, Checkpoint::DISTANCE,0,0,true));

        //gm->addObjectToRenderAfterRenderCamera(checkpoints.back());
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
        checkpoints.push_back(new Checkpoint(gm, x,y,z,false));
        //gm->addObjectToRenderAfterRenderCamera(checkpoints.back());
    }
    //qDebug()<<"Exit from creation of random checkpoints"<<endl;
}

void GameMineCrisis::addRandomMeteorites()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    GLfloat x,y,z;
    meteorites.push_back(new Meteorite(gm, 0,0,0));
    //gm->addObjectToRenderAfterRenderCamera(meteorites.back());
    for(int i=0;i<GameMineCrisis::NUMBER_OF_METEORITES-1;i++)
    {
        do
        {
            x=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            y=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
            z=(qrand() % ((int)sky->getSize()/2))-(qrand() % ((int)sky->getSize()/2));
        }while(isThereAnObject(x,y,z,meteorites)!=-1);
        meteorites.push_back(new Meteorite(gm, x,y,z));
        //gm->addObjectToRenderAfterRenderCamera(meteorites.back());
    }
    //qDebug()<<"Exit from creation of random meteorites"<<endl;

}

void GameMineCrisis::gameOver()
{
    player->stop();
    sky->stop();
    this->gameover = true;
    backgroundMusic->stop();
    if (turboEffect->state() == QMediaPlayer::PlayingState)
        turboEffect->stop();
}

void GameMineCrisis::update()
{
    for(int i=0;i<meteorites.size();i++)
        if(dynamic_cast<Meteorite*>(meteorites[i])!=NULL)
        {
            Meteorite*meteorite=dynamic_cast<Meteorite*>(meteorites[i]);
            meteorite->hit(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20);
        }
    timerGame-=0.01;
    if(isThereAnObject(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20,meteorites)!=-1)
        gameOver();
    if(isThereAnObject(camera->getEyeX()+player->getShiftX()*20,camera->getEyeY()+player->getShiftY()*20,camera->getEyeZ()+player->getShiftZ()*20,obstacles)!=-1)
        gameOver();
    int indexOfObject=isThereAnObject(camera->getEyeX(),camera->getEyeY(),camera->getEyeZ(),checkpoints);
    if(indexOfObject==0)
    {
        checkpointEffect->play();
        //checkpoints[indexOfObject]->setAlive(false);
        checkpoints.remove(indexOfObject);
        if(!checkpoints.empty())
        {
            Checkpoint* checkpoint=dynamic_cast<Checkpoint*>(checkpoints.front());
            if(checkpoint!=NULL)
                checkpoint->setActive(true);
        }
        timerGame+=Checkpoint::ADDITIONAL_TIME;
        numberOfcheckpoint--;
    }
    if(timerGame<0.1)
    {
        timerGame=0.0;
        gameOver();
    }
    hud_timerGame.clear();
    hud_timerGame.append("Timer: ");
    hud_timerGame.append (QString::number(timerGame, 'f', 3));
    hud_checkpoints.clear();
    hud_checkpoints.append("Checkpoints: ");
    hud_checkpoints.append (QString::number(numberOfcheckpoint));
}

void GameMineCrisis::loopBackgroundMusic(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::QMediaPlayer::EndOfMedia)
        backgroundMusic->play();
}

void GameMineCrisis::loopTurboEffect(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::QMediaPlayer::EndOfMedia)
        turboEffect->play();
}
