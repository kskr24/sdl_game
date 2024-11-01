#include "Game.hpp"
#include <SDL2/SDL.h>


// TODO(kskr24) Use glog library for logging

bool Game::init(const char *title, int xpos, int ypos, int width, int height,
                int flags) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    // std::cout << "SDL Init Success\n";
    // extern SDL_Window *g_pWindow;
    // Init the window
    m_pWindow =
        SDL_CreateWindow("Hello World", xpos, ypos, width, height, flags);

    if (m_pWindow != NULL) {
      // std::cout << "Window  Creation Sucessfull\n";

      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      if (m_pRenderer != NULL) {
        // std::cout << "render creation sucessfull\n";
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
      } else {
        // std::cout << "render init fail\n";
        return false;
      }
    } else {
      // std::cout << "window init fail\n";
      return false;
    }
  } else {
    // std::cout << "SDL init fail\n";
    return false;
  }

  // std::cout << "init sucess\n";
  m_bRunning = true;
  return true;
}

void Game::render() {
  SDL_RenderClear(m_pRenderer);   // clear the render to draw color
  SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::clean() {
  // std::cout << "cleaning game\n";
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}

void Game::handleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT: {
      m_bRunning = false;
    } break;

    default:
      break;
    }
  }
}
