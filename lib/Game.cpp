#include "Game.hpp"

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
      SDL_Surface *p_TempSurface = SDL_LoadBMP("assets/rider.bmp");
      m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, p_TempSurface);
      SDL_FreeSurface(p_TempSurface);

      SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w,
                       &m_sourceRectangle.h);

      m_destinationRectangle.x = m_sourceRectangle.x = 0;
      m_destinationRectangle.y = m_sourceRectangle.y = 0;
      m_destinationRectangle.w = m_sourceRectangle.w;
      m_destinationRectangle.h = m_sourceRectangle.h;
      if (m_pRenderer != NULL) {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
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
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle,
                 &m_destinationRectangle);
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

bool Game::running() { return m_bRunning; }
