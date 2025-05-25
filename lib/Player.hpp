#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>

#include "GameObject.hpp"

class Player : public GameObject {
 public:
  void load(int x, int y, int width, int height, std::string textureID);
  void draw(SDL_Renderer* p_Renderer);
  void update();
  void clean();
};

#endif
