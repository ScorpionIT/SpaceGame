#include "obstacle.h"

Obstacle::Obstacle(GLfloat x, GLfloat y, GLfloat z)
{
    setPosition (x, y, z);
    setSize(SIZE, SIZE, SIZE);
}

void Obstacle::render()
{
    glPushMatrix();
    glTranslatef(getPositionX()-SIZE/2,getPositionY()-SIZE/2,getPositionZ()-SIZE/2);
    glColor4f(1, 0, 0, 1);

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
    glPopMatrix();
}
