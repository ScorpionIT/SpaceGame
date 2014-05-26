#include "obstacle.h"



Obstacle::Obstacle(GLfloat x, GLfloat y, GLfloat z): EngineObject(x,y,z)
{
}

void Obstacle::render()
{
    glColor3ub((GLubyte) 255,(GLubyte) 0,(GLubyte) 0 );
    glTranslatef(getPositionX(),getPositionY(),getPositionZ());
    glBegin(GL_QUADS);
            // Front Face
            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);


        // Back Face
            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

        // Top Face
            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

        // Bottom Face
            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

        // Left face
            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);

        // Right face
            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,-Obstacle::SIZE);

            glVertex3f(-Obstacle::SIZE,-Obstacle::SIZE,Obstacle::SIZE);
            glEnd();
}

GLfloat Obstacle::getSize()
{
    return Obstacle::SIZE;
}


