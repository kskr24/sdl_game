#include "Game.hpp"

#include "lib/TextureManager.hpp"

#include <SDL2/SDL_image.h>

typedef TextureManager TheTextureManager;
// TODO(kskr24) Use glog library for logging
bool Game::init(const char *title,
                int         xpos,
                int         ypos,
                int         width,
                int         height,
                int         fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  m_pWindow = SDL_CreateWindow("Hello World", xpos, ypos, width, height, flags);
  if (m_pWindow == NULL) {
    return false;
  }

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
  if (m_pRenderer == NULL) {
    return false;
  }

  SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
  if (!TheTextureManager::Instance()->load(
          "assets/animate_alpha.png", "animate", m_pRenderer)) {
    return false;
  }

  // m_go.load(100, 100, 128, 82, "animate");
  // m_player.load(300, 300, 128, 82, "animate");

  m_bRunning = true;
  return true;
}

void Game::render() {
  SDL_RenderClear(m_pRenderer);  // clear the render to draw color
  TextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);
  TextureManager::Instance()->drawFrame(
      "animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);

  SDL_RenderPresent(m_pRenderer);  // draw to the screen
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
        m_bRunning = true;
      } break;

      default:
        break;
    }
  }
}
void Game::update() { m_currentFrame = int(((SDL_GetTicks() / 100) % 6)); }
bool Game::running() { return m_bRunning; }
