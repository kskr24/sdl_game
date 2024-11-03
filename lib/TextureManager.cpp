#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id,
                          SDL_Renderer *p_Renderer) {
  SDL_Surface *p_TempSurface = IMG_Load(fileName.c_str());
  if (p_TempSurface == NULL) {
    return false;
  }

  SDL_Texture *pTexture =
      SDL_CreateTextureFromSurface(p_Renderer, p_TempSurface);
  SDL_FreeSurface(p_TempSurface);

  if(p_TempSurface != 0){
    m_textureMap[id] = pTexture;
    return true;
  }

  return false;
}

void 
