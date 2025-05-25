#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>

#include <map>
#include <string>
class TextureManager {
 public:
  static TextureManager *Instance();
  bool load(std::string fileName, std::string id, SDL_Renderer *p_Renderer);

  void draw(std::string   id,
            int           x,
            int           y,
            int           width,
            int           height,
            SDL_Renderer *p_Renderer,
            SDL_FlipMode = SDL_FLIP_NONE);

  void drawFrame(std::string   id,
                 int           x,
                 int           y,
                 int           width,
                 int           height,
                 int           currentRow,
                 int           currentFrame,
                 SDL_Renderer *p_Renderer,
                 SDL_FlipMode = SDL_FLIP_NONE);

 private:
  TextureManager() {};
  std::map<std::string, SDL_Texture *> m_textureMap;
  static TextureManager               *s_pInstance;
};

#endif
