#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <iostream>

class Game {
public:
  Game() {}
  ~Game() {}

  bool init(const char *title, int xpos, int ypos, int width, int height,
            int fullscreen);
  void render();
  void update(){}
  void handleEvents();
  void clean();

  bool running();

private:
  bool m_bRunning;
  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;

  SDL_Texture* m_pTexture;
  SDL_Rect m_sourceRectangle;
  SDL_Rect m_destinationRectangle;
};

#endif
