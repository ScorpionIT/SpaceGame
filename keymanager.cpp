#include "keymanager.h"

KeyManager::KeyManager(QWidget *parent) :
  QWidget(parent)
{

}

void KeyManager::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Up)
       emit keyPress ("UP");
    if(event->key()==Qt::Key_Down)
        emit keyPress ("DOWN");
    if(event->key()==Qt::Key_Right)
        emit keyPress ("RIGHT");
    if(event->key()==Qt::Key_Left)
        emit keyPress ("LEFT");

    if(event->key()==Qt::Key_W)
        emit keyPress ("W");
    if(event->key()==Qt::Key_S)
        emit keyPress ("S");
}

void KeyManager::keyReleaseEvent(QKeyEvent* event)
{
  if(event->key()==Qt::Key_Up)
     emit keyRelease ("UP");
  if(event->key()==Qt::Key_Down)
      emit keyRelease ("DOWN");
  if(event->key()==Qt::Key_Right)
      emit keyRelease ("RIGHT");
  if(event->key()==Qt::Key_Left)
      emit keyRelease ("LEFT");

  if(event->key()==Qt::Key_W)
      emit keyRelease ("W");
  if(event->key()==Qt::Key_S)
      emit keyRelease ("S");
}
