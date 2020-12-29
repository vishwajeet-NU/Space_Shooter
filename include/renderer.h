/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

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

struct BackGroundColor
{
    SDL_Color Black = {0x1E, 0x1E, 0x1E, 0xFF};
    SDL_Color Blue = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color Brown = {0x3A, 0x00, 0x00, 0xFF};
    SDL_Color Green = {0x73, 0xA6, 0x73, 0xFF};
    
};


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();
  
  void Render(std::vector<enemy*> &ArrayEnemies, std::vector<bullet*> &PlayerBullets, std::vector<bullet*> &BossBullets, std::vector<bullet*> &EnemyBullets, 
  player &player_one, boss * boss_enemy_one, int NumberOfEnemies, int Score, SDL_Color &_backColor, int level);
  
  void Render(std::string Message,SDL_Color &_backColor);
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font *Font = NULL;
  SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

  void RenderText( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
  void loadMedia(std::string text); 
  void fillarray(std::vector<enemy*> &ArrayEnemies, int &NumberOfEnemies, SDL_Rect *arr);
  void fillarray(std::vector<bullet*> &Bullets, SDL_Rect *arr);

  void RenderBullets(std::vector<bullet*> &Bullets, SDL_Rect *arr );
  void RenderTextbar(int Score,player &player_one,boss * boss_enemy_one,int level);
  void RenderObjects(player &player_one,std::vector<enemy*> &ArrayEnemies, SDL_Rect *enemy_array, int &NumberOfEnemies, boss * boss_enemy_one);

  void LoadText(std::string textureText);
	void RenderFont( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif