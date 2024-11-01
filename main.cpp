#include "Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>


int main(int argc, char *argv[]) {
  // Initialize SDL
  std::unique_ptr<Game> g_ptr{new Game()};
  g_ptr->init("Setting Up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
              640, 480, SDL_WINDOW_FULLSCREEN);

  while (g_ptr->running()) {
    g_ptr->handleEvents();
    g_ptr->update();
    g_ptr->render();
  }
  return 0;
}
