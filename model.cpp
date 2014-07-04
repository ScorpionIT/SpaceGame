#include "model.h"

Model::Model()
{

}

void Model::loadModel(QString filePath)
{
    QString currentMaterial;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int lineNumber = 1;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line[0] != '#' && !line.isEmpty())
        {
            if (line.mid(0,6) == "mtllib")
            {
                QString mtlPath = filePath.remove(filePath.section("/",-1));
                mtlPath.append(line.mid(7));
                loadmtl(mtlPath);
            }
            else if (line.mid(0,6) == "usemtl")
            {
                currentMaterial = line.mid(7);
            }
            else if (line.mid(0,2) == "v ")
            {
                float x = line.mid(2).section(" ",0,0).toFloat();
                float y = line.mid(2).section(" ",1,1).toFloat();
                float z = line.mid(2).section(" ",2,2).toFloat();
                float w = line.mid(2).section(" ",-1).toFloat();
                if (w == z)
                    w = 0;
                vertices.append (Vertex (x, y, z, w));
            }
            else if (line.mid(0,2) == "f ")
            {
                QVector<Face> tmp_face;
                int numberFace = line.mid(3).count(" ");
                for (int i = 0; i <= numberFace; i++)
                {
                    QString face = line.mid(2).section(" ", i, i);
                    int vIndex = face.section("/", 0, 0).toInt();
                    if (vIndex == 0)
                        qDebug() << "Problema linea: " << lineNumber << face;
                    int vtIndex = face.section("/", 1, 1).toInt();
                    int vnIndex = face.section("/", 2, 2).toInt();
                    if (currentMaterial.isEmpty())
                        tmp_face.append (Face (vIndex, vtIndex, vnIndex));
                    else
                        tmp_face.append (Face (vIndex, vtIndex, vnIndex, currentMaterial));
                    faces.append(tmp_face);
                }
            }
            else if (line[0] == 'o')
            {
                if (WARNING)
                    qDebug() << "TODO: keyword o (line " << lineNumber << ")";
            }
            else if (line[0] == 's')
            {
                if (WARNING)
                    qDebug() << "TODO: keyword s (line " << lineNumber << ")";
            }
            else if (line[0] == 'g')
            {
                if (WARNING)
                    qDebug() << "TODO: keyword g (line " << lineNumber << ")";
            }
            else if (line.mid(0,2) == "vt")
            {
                int space = line.mid(3).count(" ");
                float u = line.mid(3).section(" ", 0, 0).toFloat();
                float v;
                float w;
                if (space >= 1)
                    v = line.mid(3).section(" ", 1,1).toFloat();
                else
                    v = 0;
                if (space == 2)
                    w = line.mid(3).section(" ", -1).toFloat();
                else
                    w = 0;
                textures.append(Texture (u, v, w));
            }
            else if (line.mid(0,2) == "vn")
            {
                float i = line.mid(3).section(" ", 0, 0).toFloat();
                float j = line.mid(3).section(" ", 1, 1).toFloat();
                float k = line.mid(3).section(" ", -1).toFloat();
                normals.append(Normal (i, j, k));
            }
            else
                qDebug() << "Linea " << lineNumber <<  "non riconosciuta: " << line;
        }
        lineNumber++;
    }
    file.close();
}


void Model::drawModel()
{
    renderModel();
}

void Model::calcDim()
{
    int maxX = vertices[0].x;
    int minX = vertices[0].x;

    int maxY = vertices[0].y;
    int minY = vertices[0].y;

    int maxZ = vertices[0].z;
    int minZ = vertices[0].z;

    for (int i= 0; i< vertices.size(); i++)
    {
        if (vertices[i].x > maxX)
            maxX = vertices[i].x;
        if (vertices[i].x < minX)
            minX = vertices[i].x;

        if (vertices[i].y > maxY)
            maxY = vertices[i].y;
        if (vertices[i].y < minY)
            minY = vertices[i].y;

        if (vertices[i].z > maxZ)
            maxZ = vertices[i].z;
        if (vertices[i].z < minZ)
            minZ = vertices[i].z;
    }

    if (maxX < 0)
        maxX = maxX * -1;
    if (minX < 0)
        minX = minX * -1;

    if (maxY < 0)
        maxY = maxY * -1;
    if (minY < 0)
        minY = minY * -1;

    if (maxZ < 0)
        maxZ = maxZ * -1;
    if (minZ < 0)
        minZ = minZ * -1;

    ms.width = maxX+minX;
    ms.height = maxY+minY;
    ms.depth = maxZ+maxZ;
    ms.calculed = true;
}

ModelSize Model::getDim()
{
    return ms;
}

void Model::loadmtl (QString mtlPath)
{
    QString mtlName;
    QFile file(mtlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    int lineNumber = 1;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line[0] != '#' && !line.isEmpty())
        {
            if (line.mid(0,6) == "newmtl")
            {
                mtlName = line.mid(7);
                materials.insert(mtlName,Material());
            }
            else if (!mtlName.isEmpty())
            {
                if (line.mid(0,2) == "Ka")
                {
                    float r = line.mid(3).section(" ",0,0).toFloat();
                    float g = line.mid(3).section(" ",1,1).toFloat();
                    float b = line.mid(3).section(" ",2,2).toFloat();
                    materials[mtlName].Ka[0] = r;
                    materials[mtlName].Ka[1] = g;
                    materials[mtlName].Ka[2] = b;
                }
                else if (line.mid(0,2) == "Kd")
                {
                    float r = line.mid(3).section(" ",0,0).toFloat();
                    float g = line.mid(3).section(" ",1,1).toFloat();
                    float b = line.mid(3).section(" ",2,2).toFloat();
                    materials[mtlName].Kd[0] = r;
                    materials[mtlName].Kd[1] = g;
                    materials[mtlName].Kd[2] = b;
                }
                else if (line.mid(0,2) == "Ks")
                {
                    float r = line.mid(3).section(" ",0,0).toFloat();
                    float g = line.mid(3).section(" ",1,1).toFloat();
                    float b = line.mid(3).section(" ",2,2).toFloat();
                    materials[mtlName].Ks[0] = r;
                    materials[mtlName].Ks[1] = g;
                    materials[mtlName].Ks[2] = b;
                }

                else if (line.mid(0,2) == "Ns")
                {
                    float ns = line.mid(3).toFloat();
                    materials[mtlName].Ns = ns;
                }
                else if (line.mid(0,6) == "map_Kd")
                {
                    QString texturePath = mtlPath.remove(mtlPath.section("/",-1));
                    texturePath.append(line.mid(7));
                    materials[mtlName].textureID = loadTexture(texturePath);
                }
                else
                    if (WARNING)
                        qDebug() << "Linea mtl " << lineNumber <<  "non riconosciuta: " << line;
            }
            else
                if (WARNING)
                    qDebug() << "Nome materiale non dichiarato (is mtl?)" << endl;

        }
        lineNumber++;
    }
    file.close();

}

GLuint Model::loadTexture(QString imgPath)
{
    QImage im;
    im.load(imgPath);
    QImage image = QGLWidget::convertToGLFormat (im);
    if (image.isNull())
        qDebug() << "Impossibile caricare la texture " << imgPath << endl;
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGBA,                       //Format OpenGL uses for image
                 image.width(), image.height(),  //Width and height
                 0,                            //The border of the image
                 GL_RGBA, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image.bits());               //The actual pixel data
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.width() , image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    return textureId; //Returns the id of the texture
}

void Model::renderModel(bool useTexture)
{
    QString currentMaterial;
    if (useTexture)
        glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < faces.size(); i++)
    {
        //Set Materials
        if (currentMaterial != faces[i][0].mIndex && !faces[i][0].mIndex.isEmpty())
        {
            currentMaterial = faces[i][0].mIndex;
            glMaterialfv(GL_FRONT, GL_SPECULAR, materials[currentMaterial].Ks);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[currentMaterial].Kd);
            glMaterialfv(GL_FRONT, GL_AMBIENT, materials[currentMaterial].Ka);
            glMaterialf(GL_FRONT, GL_SHININESS, materials[currentMaterial].Ns);

            glColor4fv(materials[currentMaterial].Kd);

            if (materials[currentMaterial].textureID != 0)
            {
                glBindTexture(GL_TEXTURE_2D, materials[currentMaterial].textureID);
                /*glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
        }

        glBegin (GL_POLYGON);
        for (int k = 0; k < faces[i].size(); k++)
        {
            // Set vertex Normal
            glNormal3f (normals[faces[i][k].vnIndex-1].i,  normals[faces[i][k].vnIndex-1].j,  normals[faces[i][k].vnIndex-1].k);

            // Draw texture cordinates
            glTexCoord2f (textures[faces[i][k].vtIndex-1].u, textures[faces[i][k].vtIndex-1].v);

            //Draw vertex
            glVertex3f (vertices[faces[i][k].vIndex-1].x, vertices[faces[i][k].vIndex-1].y, vertices[faces[i][k].vIndex-1].z);

        }
        glEnd ();
    }
    if (useTexture)
        glDisable(GL_TEXTURE_2D);
}

GLuint Model::getGlList(bool useTexture)
{
    GLuint modelList;
    modelList = glGenLists(1);
    glNewList (modelList, GL_COMPILE);
    renderModel(useTexture);
    glEndList();
    return modelList;
}


QString Model::getModelInfo()
{
    QString info;
    info.append ("Vertices: ");
    info.append (QString::number(vertices.size()));

    info.append ("\nTextures vertex: ");
    info.append (QString::number(textures.size()));

    info.append ("\nNormals: ");
    info.append (QString::number(textures.size()));

    if (ms.calculed)
    {
        info.append("\nModel Size: ");
        info.append(QString::number(ms.width));
        info.append(",");
        info.append(QString::number(ms.height));
        info.append(",");
        info.append(QString::number(ms.depth));

    }
    return info;
}

void Model::scaleModel (float scale)
{
    ms.calculed = false;
    for (int i= 0; i< vertices.size(); i++)
    {
        vertices[i].x = vertices[i].x*scale;
        vertices[i].y = vertices[i].y*scale;
        vertices[i].z = vertices[i].z*scale;
    }
}
