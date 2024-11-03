#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject {
 public:
  void draw() { GameObject::draw(); }

  void update() {
    m_x = 0;
    m_y = 0;
  }

  void clean() { GameObject::clean(); }
};

#endif
