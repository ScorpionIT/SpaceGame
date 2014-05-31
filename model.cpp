#include "model.h"
#include <QDebug>

Model::Model(const char *modelPath)
{
   model = newobj();
   /*int ret =*/ parse_obj((char*)modelPath, model); //Controllare valore ritorno
   //qDebug() << ret << endl;
}

obj_t* Model::getModel()
{
    return model;
}
