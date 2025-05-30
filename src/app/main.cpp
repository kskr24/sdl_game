
#include "lib/Game.hpp"

#include <SDL3/SDL.h>

#include <memory>

int main(int argc, char *argv[]) {
  // Initialize SDL
  std::unique_ptr<Game> g_ptr{new Game()};
  g_ptr->init("Setting Up SDL",
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED,
              640,
              480,
              true);

  while (g_ptr->running()) {
    g_ptr->handleEvents();
    g_ptr->update();
    g_ptr->render();

    // SDL_Delay(10);
  }

  return 0;
}
