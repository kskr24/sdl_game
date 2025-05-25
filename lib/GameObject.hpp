#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL3/SDL.h>

#include <string>
class GameObject {
 public:
  void load(int x, int y, int width, int height, std::string textureID);
  void draw(SDL_Renderer* p_Renderer);
  void update();
  void clean();

 protected:
  std::string m_textureID;

  int m_currentFrame;
  int m_currentRow;
  int m_x;
  int m_y;
  int m_width;
  int m_height;
};
#endif
