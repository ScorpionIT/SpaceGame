#ifndef HUDMESSAGESYSTEM_H
#define HUDMESSAGESYSTEM_H

#include <QObject>
#include <QGLWidget>
#include <QString>
#include <QDebug>
#include <QMap>

struct HudString
{
    QFont font;
    QColor color;
    QString hud;
    int x;
    int y;

    HudString (int x, int y, QString hudText, QFont font, QColor color)
    {
        this->x = x;
        this->y = y;
        this->hud = hudText;
        this->font = font;
        this->color = color;
    }
};

class HudMessageSystem : public QObject
{
    Q_OBJECT

public:
    HudMessageSystem(QGLWidget *ge, QObject *parent = 0);
    void setText(QString key, QString text, QFont font, QColor color);
    void setText(QString key, QString text, GLfloat x, GLfloat y, bool center, QFont font, QColor color);
    void removeText (QString key);
    QMap<QString, HudString *>* getHudStrings();

private:
    QGLWidget* ge;
    QMap<QString, HudString*>* HudStrings;

signals:

public slots:

};

#endif // HUDMESSAGESYSTEM_H
