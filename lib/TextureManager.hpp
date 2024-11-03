#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

class TextureManager {
public:
  bool load(std::string fileName, std::string id, SDL_Renderer *p_Renderer);

  void draw(std::string id, int x, int y, int width, int height,
            SDL_RendererFlip = SDL_FLIP_NONE);
  void drawFrame(std::string &id, int x, int y, int width, int height,
                 SDL_Renderer *p_Renderer, SDL_RendererFlip = SDL_FLIP_NONE);

private:
  std::map<std::string, SDL_Texture *> m_textureMap;
};

#endif
