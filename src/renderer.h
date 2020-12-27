#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "base.h"
#include "enemy.h"
#include "player.h"
#include "boss_enemy.h"
#include "bullet.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();
  
  void Render(std::vector<enemy*> &ArrayEnemies, std::vector<bullet*> &PlayerBullets, std::vector<bullet*> &BossBullets, std::vector<bullet*> &EnemyBullets, 
  player &player_one, boss * boss_enemy_one, int NumberOfEnemies, int Score);
    
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font *gFont = NULL;
  SDL_Texture* mTexture;

	int mWidth{30};
	int mHeight{30};


  void RenderText( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
  void loadMedia(std::string text); 

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif