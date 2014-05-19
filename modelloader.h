#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <QObject>
#include <QString>
#include "glm/glm.h"

class ModelLoader : public QObject
{
    Q_OBJECT
public:
    ModelLoader(QObject *parent);
    ModelLoader(const char *modelPath);

    void loadModel (const char *modelPath);
    void renderModel ();

private:
    GLMmodel* model;

signals:

public slots:

};

#endif // MODELLOADER_H
