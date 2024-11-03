#include "Game.hpp"

#include <SDL2/SDL_image.h>
#include "lib/TextureManager.hpp"
// TODO(kskr24) Use glog library for logging

bool Game::init(const char *title, int xpos, int ypos, int width, int height,
                int fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

    int flags = 0;
    if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
    }
    m_pWindow =
        SDL_CreateWindow("Hello World", xpos, ypos, width, height, flags);

    if (m_pWindow != NULL) {

      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      // check for loding

      m_textureManager.load("assets/animate_alpha.png", "animate", m_pRenderer);

      if (m_pRenderer != NULL) {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }

  m_bRunning = true;
  return true;
}

void Game::render() {
  SDL_RenderClear(m_pRenderer); // clear the render to draw color
  m_textureManager.draw("animate", 0, 0, 128, 82, m_pRenderer);
  m_textureManager.drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame,
                             m_pRenderer);
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
void Game::update() {
  m_currentFrame = 128 * int(((SDL_GetTicks() / 100) % 6));
}
bool Game::running() { return m_bRunning; }
