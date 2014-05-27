#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "opengl.h"
#include <QObject>
#include "libObj/include/object.h"

class Model : public QObject
{

public:
    Model(const char *modelPath);
    obj_t* getModel();

protected:
    obj_t* model;

private:
  //  obj_t *model;

};

#endif // MODELLOADER_H
