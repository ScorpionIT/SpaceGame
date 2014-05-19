#include "modelloader.h"

#include <QDebug>

ModelLoader::ModelLoader(QObject *parent) :
    QObject(parent)
{

}

ModelLoader::ModelLoader(const char* modelPath)
{
    loadModel(modelPath);
}

void ModelLoader::loadModel (const char* modelPath)
{
    model = glmReadOBJ(modelPath);
    if (!model)
        qDebug() << "Impossibile caricare il modello " << modelPath << endl;

    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0, GL_TRUE);
}

void ModelLoader::renderModel ()
{
    glmDraw(model, GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
}
