#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>

class Game {
public:
  Game() {}
  ~Game() {}

  bool init(const char *title, int xpos, int ypos, int width, int height,
            int flags);
  void render();
  void update();
  void handleEvents();
  void clean();

  const bool &running() const;

private:
  bool m_bRunning;
  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;
};
#endif
