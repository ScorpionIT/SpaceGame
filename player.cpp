#include "player.h"

Player::Player()
{
    setPosition(0,0,0);
    model = new ModelLoader("data/obj/snail/snail.obj");
}

bool Player::hasTexture()
{
    return false;
}

QString Player::getTexturePath()
{
  //return QString ("data/model/snail/snail_tex_red.png");
  return QString ("data/model/MP5K/Tex_0004_1.bmp");
}

void Player::render()
{
    glRotated (90, 0, 0, 1);
    glRotated (90, 1, 0, 0);
    //glScaled();
    model->renderModel();
}

GLfloat Player::getSize()
{
    return 0;
}
