#include "modelloader.h"
#include <QDebug>

ModelLoader::ModelLoader(char *modelPath)
{
   model = newobj();
   int ret = parse_obj(modelPath, model); //Controllare valore ritorno
   qDebug() << ret << endl;
}

void ModelLoader::renderModel()
{
    glRenderObj(model);
}
