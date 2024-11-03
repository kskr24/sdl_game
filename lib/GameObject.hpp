#ifndef GAME_OBJECT
#define GAME_OBJECT

class GameObject {
 public:
  void draw() {}
  void update() {}
  void clean() {}

 protected:
  int m_x;
  int m_y;
};
#endif
