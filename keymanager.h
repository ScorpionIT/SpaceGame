#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QWidget>
#include <QKeyEvent>

class KeyManager : public QWidget
{
  Q_OBJECT
public:
  explicit KeyManager(QWidget *parent = 0);

protected:
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent* event);

signals:
  void keyPress (QString key);
  void keyRelease (QString key);

public slots:

};

#endif // KEYMANAGER_H
