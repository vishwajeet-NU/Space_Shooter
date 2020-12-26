#include "controller.h"
#include <iostream>
#include "SDL.h"


void Controller::Move(Direction dir, player &Player_one) const
{
  int speed;
  SDL_Point player_location; 
  Player_one.GetBodySpeed(speed);
  Player_one.GetBodyLocation(player_location);

  int updated_x = player_location.x + dir * speed;
  int updated_y = player_location.y;

  if(updated_x > (ScreenWidth - 30))
  {
    updated_x = ScreenWidth -30;
  }
  if(updated_x < 30 )
  {
    updated_x = 30;
  }

  Player_one.SetBodyLocation( updated_x, updated_y );
}

void Controller::Shoot(player &Player_one, std::vector<bullet*> &Player_bullets) const
{
  bullet *Bullet_P = new bullet(Player_one);
  SDL_Point location;
  int width, height;
  Player_one.GetBodyDimension(width,height);
  Player_one.GetBodyLocation(location);
  int loc1 = location.x + width/2;
  int loc2 = location.y;
  Bullet_P->SetBodyLocation(loc1,loc2);

  Player_bullets.emplace_back(Bullet_P);

}

void Controller::HandleInput(bool &running, player &Player_one, std::vector<bullet*> &Player_bullets)  const
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
      switch (e.key.keysym.sym) {

        case SDLK_LEFT:
             Move(Direction::left, Player_one);
          break;
        case SDLK_RIGHT:
              Move(Direction::right, Player_one);
          break;
        case SDLK_SPACE:
              Shoot(Player_one, Player_bullets);
      }
    }

  }
}