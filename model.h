#ifndef MODEL_H
#define MODEL_H

#include <QGLWidget>
#include <QOffscreenSurface>
#include <QMap>
#include <QVector>
#include <QDebug>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QObject>
#include <GL/gl.h>
#include <GL/glu.h>


#define WARNING false

struct ModelSize
{
    bool calculed;
    unsigned int width;
    unsigned int height;
    unsigned int depth;

    ModelSize()
    {

    }

    ModelSize (unsigned int w, unsigned int h, unsigned int d)
    {
        this->width = w;
        this->height = h;
        this->depth = d;
        this->calculed = true;
    }
};

struct Vertex
{
    float x;
    float y;
    float z;
    float w;

    Vertex ()
    {

    }

    Vertex (float x, float y, float z, float w = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

struct Texture
{
    float u;
    float v;
    float w;

    Texture ()
    {
        u = 0;
        v = 0;
        w = 0;
    }

    Texture (float u, float v = 0, float w = 0)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }

};

struct Normal
{
    float i;
    float j;
    float k;

    Normal ()
    {
        this->i = 0;
        this->j = 0;
        this->k = 0;
    }

    Normal (float i, float j, float k)
    {
        this->i = i;
        this->j = j;
        this->k = k;
    }
};

struct Face
{
    int vIndex;
    int vtIndex;
    int vnIndex;
    QString mIndex; // Material

    Face ()
    {
        this->vIndex = -1;
        this->vnIndex = -1;
        this->vtIndex = -1;
    }

    Face (int vIndex, int vtIndex, int vnIndex)
    {
        this->vIndex = vIndex;
        this->vtIndex = vtIndex;
        this->vnIndex = vnIndex;
    }

    Face (int vIndex, int vtIndex, int vnIndex, QString mIndex)
    {
        this->vIndex = vIndex;
        this->vtIndex = vtIndex;
        this->vnIndex = vnIndex;
        this->mIndex = mIndex;
    }
};

struct Material
{
    float Ka[4]; //Ambient colour
    float Kd[4]; //Diffuse colour
    float Ks[4]; //Specular colour
    float Ns;    // Specular (coeff)

    GLuint textureID;

    unsigned int illum;

    Material ()
    {
        this->Ka[0] = 0;
        this->Ka[1] = 0;
        this->Ka[2] = 0;
        this->Ka[3] = 1;

        this->Kd[0] = 0;
        this->Kd[1] = 0;
        this->Kd[2] = 0;
        this->Kd[3] = 1;

        this->Ks[0] = 0;
        this->Ks[1] = 0;
        this->Ks[2] = 0;
        this->Ks[3] = 1;

        this->Ns = 0;
        this->textureID = 0;
        this->illum = 0;
    }

};

class Model : public QOffscreenSurface
{
    Q_OBJECT

public:
    Model();

    void loadModel(QString filePath);
    void makeVBO();
    void drawModel();
    void calcDim();
    ModelSize getDim();
    void scaleModel (float scale);
    GLuint getGlList(bool useTexture=true);
    QString getModelInfo();

protected:

private:
    ModelSize ms;
    GLuint loadTexture(QString imgPath);
    void loadmtl (QString mtlPath);
    void renderModel(bool useTexture=true);
    QVector<Vertex> vertices;
    QVector< QVector<Face> > faces;
    QVector<Texture> textures;
    QVector<Normal> normals;
    QMap <QString, Material> materials;

    /*GLuint VertexVBO;
    GLuint NormalVBO;
    GLuint TextureVBO;*/

signals:

public slots:

};

#endif // MODEL_H
