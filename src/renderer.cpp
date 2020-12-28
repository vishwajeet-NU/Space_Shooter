#include "renderer.h"
#include <iostream>
#include <string>


Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height) : screen_width(screen_width), screen_height(screen_height)
  {
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

  int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	Font = TTF_OpenFont( "../fonts/AmaticSC-Regular.ttf", 48 );
	if( Font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
}

void Renderer::fillarray(std::vector<enemy*> &ArrayEnemies, int &NumberOfEnemies, SDL_Rect *arr)
{
  for(int i=0; i<NumberOfEnemies; i++)
    {
      arr[i] = *(ArrayEnemies[i]->GetRect());
    }
}

void Renderer::fillarray(std::vector<bullet*> &Bullets, SDL_Rect *arr)
{

  for(int i=0; i<Bullets.size(); i++)
  {
    arr[i] = *(Bullets[i]->GetRect());
  }
}

void Renderer::RenderBullets(std::vector<bullet*> &Bullets, SDL_Rect *arr )
{
  Color color;
  if(Bullets.size()>0)
  {
    Bullets[0]->ColorGetter(color);
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRects(sdl_renderer, arr, Bullets.size());
  }  
}

void Renderer::RenderTextbar(int Score,player &player_one,boss * boss_enemy_one)
{
  std::string title{"Score: " + std::to_string(Score) + "     Player Health : " + std::to_string(player_one.GetHealth()) + "      Boss Health : "
  + std::to_string(boss_enemy_one->GetHealth())};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderObjects(player &player_one,std::vector<enemy*> &ArrayEnemies, SDL_Rect *enemy_array, int &NumberOfEnemies, boss * boss_enemy_one)
{
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
  if(boss_enemy_one->LifeStatus())
  {
    boss_enemy_one->ColorGetter(color);
    block = *(boss_enemy_one->GetRect());
    SDL_SetRenderDrawColor(sdl_renderer, color.red, color.green, color.blue, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }
}

void Renderer::Render(std::vector<enemy*> &ArrayEnemies, std::vector<bullet*> &PlayerBullets, std::vector<bullet*> &BossBullets, std::vector<bullet*> &EnemyBullets, 
  player &player_one, boss * boss_enemy_one, int NumberOfEnemies, int Score)
{

  SDL_Rect enemy_array[NumberOfEnemies] , player_bullet_array[PlayerBullets.size()] , boss_bullet_array[BossBullets.size()], 
  enemy_bullet_array[EnemyBullets.size()];

  fillarray(ArrayEnemies,NumberOfEnemies,enemy_array);
  fillarray(PlayerBullets,player_bullet_array);
  fillarray(BossBullets,boss_bullet_array);
  fillarray(EnemyBullets,enemy_bullet_array);

  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  RenderObjects(player_one,ArrayEnemies,enemy_array,NumberOfEnemies,boss_enemy_one);

  RenderBullets(BossBullets,boss_bullet_array);
  RenderBullets(PlayerBullets,player_bullet_array);
  RenderBullets(EnemyBullets,enemy_bullet_array);

  RenderTextbar(Score,player_one,boss_enemy_one);

  // // Update Screen
  SDL_RenderPresent(sdl_renderer);

}

void Renderer::LoadText(std::string textureText)
{
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF };	
	SDL_Surface* textSurface = TTF_RenderText_Solid( Font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
    mTexture = SDL_CreateTextureFromSurface( sdl_renderer, textSurface );
	  if( mTexture == NULL )
	  	{
	  		printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	  	}
	  else
	  	{
	  		//Get image dimensions
	  		mWidth = textSurface->w;
	  		mHeight = textSurface->h;
	  	}
	  	//Get rid of old surface
	  	SDL_FreeSurface( textSurface );
  } 
}


void Renderer::RenderFont( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx( sdl_renderer, mTexture, clip, &renderQuad, angle, center, flip );
}



void Renderer::Render(std::string Message)
{
  // // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  SDL_SetWindowTitle(sdl_window, Message.c_str());
  LoadText(Message);
  RenderFont( (ScreenWidth - mWidth)/2 , (ScreenWidth - mHeight)/2);
  SDL_RenderPresent(sdl_renderer);
  
}


Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);

  SDL_Quit();
}
