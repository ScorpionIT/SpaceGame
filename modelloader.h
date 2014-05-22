#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "opengl.h"
#include <QObject>
#include "libObj/include/object.h"

class ModelLoader : public QObject
{

public:
    ModelLoader(char *modelPath);
    void renderModel();

protected:


private:
    obj_t *model;

};

#endif // MODELLOADER_H
