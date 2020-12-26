#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include "base.h"
#include "enemy.h"
#include "player.h"
#include "boss_enemy.h"
#include "bullet.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  
  void Render(std::vector<enemy*> &ArrayEnemies, std::vector<bullet*> &PlayerBullets, std::vector<bullet*> &BossBullets, std::vector<bullet*> &EnemyBullets, 
  player &player_one, boss * boss_enemy_one, int NumberOfEnemies);
    
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif