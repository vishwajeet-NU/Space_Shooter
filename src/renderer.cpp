#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

void Renderer::Render(std::vector<enemy*> &ArrayEnemies, std::vector<bullet*> &PlayerBullets, std::vector<bullet*> &BossBullets, std::vector<bullet*> &EnemyBullets, 
  player &player_one, boss * boss_enemy_one, int NumberOfEnemies)
{
  // SDL_Rect block;
  // block.w = screen_width / grid_width;
  // block.h = screen_height / grid_height;

  SDL_Rect enemy_array[NumberOfEnemies];
  SDL_Rect player_bullet_array[PlayerBullets.size()];
  SDL_Rect boss_bullet_array[BossBullets.size()];
  SDL_Rect enemy_bullet_array[EnemyBullets.size()];

  for(int i=0; i<NumberOfEnemies; i++)
  {
    enemy_array[i] = *(ArrayEnemies[i]->GetRect());
  }

  for(int i=0; i<PlayerBullets.size(); i++)
  {
    player_bullet_array[i] = *(PlayerBullets[i]->GetRect());
  }

  for(int i=0; i<BossBullets.size(); i++)
  {
    boss_bullet_array[i] = *(BossBullets[i]->GetRect());
  }

  for(int i=0; i<EnemyBullets.size(); i++)
  {
    enemy_bullet_array[i] = *(EnemyBullets[i]->GetRect());
  }

  // // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  Color color;

  // Player 
  player_one.ColorGetter(color);
  SDL_Rect block = *(player_one.GetRect());
  SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Enemy 
  if(ArrayEnemies.size()>0)
  {
    ArrayEnemies[0]->ColorGetter(color);
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRects(sdl_renderer, enemy_array, NumberOfEnemies);
  }


  // Boss 
  if(boss_enemy_one != nullptr)
  {
    boss_enemy_one->ColorGetter(color);
    block = *(boss_enemy_one->GetRect());
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // BossBullets 
  if(BossBullets.size()>0)
  {
    BossBullets[0]->ColorGetter(color);
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRects(sdl_renderer, boss_bullet_array, BossBullets.size());
  }


  // PlayerBullets 
  if(PlayerBullets.size()>0)
  {
    PlayerBullets[0]->ColorGetter(color);
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRects(sdl_renderer, player_bullet_array, PlayerBullets.size());
  }

  // EnemyBullets 
  if(PlayerBullets.size()>0)
  {
    PlayerBullets[0]->ColorGetter(color);
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRects(sdl_renderer, player_bullet_array, PlayerBullets.size());
  }


  // // Update Screen
  SDL_RenderPresent(sdl_renderer);


}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}
