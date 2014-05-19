#include "player.h"

#include "gameengine.h"

Player::Player()
{
    setPosition(0,0,0);
    model = GameEngine::loadModel("data/obj/snail/snail.obj");
}

void Player::render()
{
    //playerObj = new ModelLoader ("data/obj/snail/snail.obj");
  /*glRotated (100,1,0,0);
  glRotated (90,0,1,0);*/

  //playerObj->renderModel();
    model = GameEngine::loadModel("data/obj/snail/snail.obj");
    GameEngine::renderModel(model);
}
