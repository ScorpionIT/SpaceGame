#include "hudmessagesystem.h"

HudMessageSystem::HudMessageSystem(QGLWidget *ge, QObject *parent) :
    QObject(parent)
{
    this->ge = ge;
    HudStrings = new QMap<QString, HudString*>();
}

void HudMessageSystem::setText(QString key, QString text, QFont font, QColor color)
{
    this->setText (key, text, ge->width()/2, ge->height()/2, true, font, color);
}

void HudMessageSystem::setText(QString key, QString text, GLfloat x, GLfloat y, bool center, QFont font, QColor color)
{
    int strWSize; //Lunghezza stringa in pixel
    int strHSize; //Altezza stringa in pixel
    QFontMetrics fontM(font);
    if (center)
    {
        strWSize = fontM.width(text)/2;
        strHSize = fontM.height()/2;
    }
    else
    {
        strWSize = 0;
        strHSize = 0;
    }
    (*HudStrings)[key] = new HudString (x-strWSize, y+strHSize, text, font, color);
}

void HudMessageSystem::removeText(QString key)
{
    HudStrings->remove(key);
}

QMap<QString, HudString *> *HudMessageSystem::getHudStrings()
{
    return HudStrings;
}

