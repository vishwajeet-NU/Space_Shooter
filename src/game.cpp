#include "game.h"
#include <memory>
#include <thread>



Game::Game():_NumberOfEnemies(36), _EnemyStart_x(30), _EnemyStart_y(100),_EnemyGapSize_x(80), _EnemyGapSize_y(50), _status(true), engine(dev())
{
    _boss_direction = Direction::left;
    _enemy_direction = Direction::left;
    int counter_x = 0; 
    int counter_y = 0;

    int x_location = _EnemyStart_x;
    int y_location = _EnemyStart_y;

    _Boss_enemy = new boss; 

    while(counter_y<sqrt(_NumberOfEnemies))
    {
        while (counter_x<sqrt(_NumberOfEnemies))
        {
            enemy *single_enemy = new enemy;
            // auto single_enemy = std::make_unique<enemy>;
            x_location = x_location + _EnemyGapSize_x; 
            single_enemy->SetBodyLocation(x_location, y_location);
            _Enemy_instances.emplace_back(single_enemy);
            counter_x ++;
        }        

        y_location = y_location + _EnemyGapSize_y; 
        x_location = _EnemyStart_x;

        counter_x = 0; 
        counter_y++;
    }
    
}
Game::~Game()
{

    if(_Enemy_instances.size()>0)
    {
        std::cout<<"Yup1 \n";
        for(auto itr:_Enemy_instances)
        {
            delete itr;
        }
    }
    if(_player_bullets.size()>0)
    {
        std::cout<<"Yup2 \n";

        for (auto itr:_player_bullets)
        {
            delete itr;
        }
    }
    if(_boss_bullets.size()>0)
    {
        std::cout<<"Yup3 \n";
        for (auto itr:_boss_bullets)
        {
            delete itr;
        }
    }

    if(_Boss_enemy != NULL) 
    {
        std::cout<<"Yup4 \n";
        delete _Boss_enemy;
    
    }
    std::cout<<"Cleared Heap \n";
}

void Game::MoveBoss()
{
  int speed;
  SDL_Point boss_location; 
  _Boss_enemy->GetBodySpeed(speed);
  _Boss_enemy->GetBodyLocation(boss_location);

  int updated_x = boss_location.x + _boss_direction *  speed;
  int updated_y = boss_location.y;

  if(updated_x > (ScreenWidth - 30))
  {
      _boss_direction = Direction::left;
  }
  if(updated_x < 30 )
  {
      _boss_direction = Direction::right;
  }

  _Boss_enemy->SetBodyLocation( updated_x, updated_y );

}

void Game::MoveEnemies()
{
    int speed;
    int horizontal_speed; 
    SDL_Point enemy_location; 
    _enemy_direction = _enemy_direction == Direction::right ? Direction::left : Direction::right; 

    if(_Enemy_instances.size()>0)
    {
        for(auto itr:_Enemy_instances)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(enemy_location);
            itr->GetBodySpeedHorizontal(horizontal_speed);

            int updated_x = enemy_location.x + _enemy_direction * horizontal_speed;
            int updated_y = enemy_location.y + speed;
            itr->SetBodyLocation( updated_x, updated_y );
        }
    }
}



void Game::CreateBossBullet()
{
    if(_Boss_enemy->LifeStatus())
    {
      bullet *Bullet_B = new bullet((*_Boss_enemy));
      SDL_Point location;
      int width, height;
      _Boss_enemy->GetBodyDimension(width,height);
      _Boss_enemy->GetBodyLocation(location);
      int loc1 = location.x + width/2;
      int loc2 = location.y + height;
      Bullet_B->SetBodyLocation(loc1,loc2);
      _boss_bullets.emplace_back(Bullet_B);
    }
}

void Game::CreateEnemyBullet()
{
    if(_Enemy_instances.size()>0)
    {
        std::uniform_int_distribution<int> random_enemy(0,_NumberOfEnemies-1);
        int index = random_enemy(engine);
        enemy *source_enemy = _Enemy_instances[index];
        if(source_enemy->LifeStatus())
        {
            bullet *Bullet_E = new bullet((*source_enemy));
            SDL_Point location;
            int width, height;
            source_enemy->GetBodyDimension(width,height);
            source_enemy->GetBodyLocation(location);
            int loc1 = location.x + width/2;
            int loc2 = location.y + height;
            Bullet_E->SetBodyLocation(loc1,loc2);
            _enemy_bullets.emplace_back(Bullet_E);
        }
    }
}

void Game::MovePlayerBullets()
{
    int speed;
    SDL_Point bullet_location; 

    if(_player_bullets.size()>0)
    {
        int counter = 0; 
        for(auto itr:_player_bullets)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(bullet_location);

            int updated_x = bullet_location.x;
            int updated_y = bullet_location.y - speed;
            if(updated_y < 10)
            {
                delete itr;
                _player_bullets.erase(_player_bullets.begin()+counter);
                break;
            }

            itr->SetBodyLocation( updated_x, updated_y );
            counter++;
        }
    
    }

}


void Game::MoveBossBullets()
{
    int speed;
    SDL_Point bullet_location; 
    
    if(_boss_bullets.size()>0)
    {
        int counter = 0; 
        for(auto itr:_boss_bullets)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(bullet_location);

            int updated_x = bullet_location.x;
            int updated_y = bullet_location.y + speed;
            if(updated_y > (ScreenHeight - 10))
            {
                delete itr;
                _boss_bullets.erase(_boss_bullets.begin()+counter);
                break;
            }
            itr->SetBodyLocation( updated_x, updated_y );
            counter++;
        }
    }
}


void Game::MoveEnemyBullets()
{
    int speed;
    SDL_Point bullet_location; 
    
    if(_enemy_bullets.size()>0)
    {
        int counter = 0; 
        for(auto itr:_enemy_bullets)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(bullet_location);

            int updated_x = bullet_location.x;
            int updated_y = bullet_location.y + speed;
            if(updated_y > (ScreenHeight - 10))
            {
                delete itr;
                _enemy_bullets.erase(_enemy_bullets.begin()+counter);
                break;
            }
            itr->SetBodyLocation( updated_x, updated_y );
            counter++;
        }
    }
}



void Game::CheckPlayerBulletCollisions()
{
    if(_player_bullets.size()>0)
    {
        int bullet_counter = 0;

        for(auto itr:_player_bullets)
        {
            int enemy_counter = 0;
            bool bullet_ = true;

            SDL_Rect *bul = itr->GetRect();
            for(auto it:_Enemy_instances)
            {
                SDL_Rect *ene = it->GetRect();
                SDL_bool collide = SDL_HasIntersection(bul,ene);
                if(collide)
                {
                    it->ReduceLife();
                    delete itr;
                    bullet_ = false;
                    _player_bullets.erase(_player_bullets.begin()+bullet_counter);

                    if(!it->LifeStatus())
                    {
                        delete it;
                        _Enemy_instances.erase(_Enemy_instances.begin()+enemy_counter);
                        _NumberOfEnemies--;
                        break; 
                    }
                    collide = SDL_FALSE; 
                }  

                enemy_counter ++;               
            }
            if(bullet_ && _Boss_enemy->LifeStatus() )
            {

                SDL_Rect *bos = _Boss_enemy->GetRect();
                SDL_bool collide = SDL_HasIntersection(bul,bos);
                if(collide)
                {
                    _Boss_enemy->ReduceLife();
                    _player_bullets.erase(_player_bullets.begin()+bullet_counter);
                    delete itr;

                    if(!_Boss_enemy->LifeStatus())
                    {
                        delete _Boss_enemy;
                        std::cout<<"Delete boss enemy \n ";
                    }
                
                }
            }

            bullet_counter++;
        
        }
    }

}

void Game::CheckBossBulletCollisions()
{
    if(_boss_bullets.size()>0)
    {
        int bullet_counter = 0;
        for(auto itr:_boss_bullets)
        {
            SDL_Rect *bul = itr->GetRect();
            SDL_Rect *user = _Player.GetRect();
            SDL_bool collide = SDL_HasIntersection(bul,user);
            if(collide)
            {
                _Player.ReduceLife();
                delete itr;
                _boss_bullets.erase(_boss_bullets.begin()+bullet_counter);

                if(!_Player.LifeStatus())
                {
                    _status = false;
                    break; 
                }
                collide = SDL_FALSE; 
            }  

            bullet_counter++;
        }
    }
}

void Game::CheckEnemyBulletCollisions()
{
    if(_enemy_bullets.size()>0)
    {
        int bullet_counter = 0;
        for(auto itr:_enemy_bullets)
        {
            SDL_Rect *bul = itr->GetRect();
            SDL_Rect *user = _Player.GetRect();
            SDL_bool collide = SDL_HasIntersection(bul,user);
            if(collide)
            {
                _Player.ReduceLife();
                delete itr;
                _enemy_bullets.erase(_enemy_bullets.begin()+bullet_counter);

                if(!_Player.LifeStatus())
                {
                    _status = false;
                    break; 
                }
                collide = SDL_FALSE; 
            }  

            bullet_counter++;
        }
    }
}

void Game::Update(bool move_enemies)
{
    MoveBoss();
    if(move_enemies)
    {
        MoveEnemies();
        CreateBossBullet();
        CreateEnemyBullet();
    }
    MovePlayerBullets();
    MoveBossBullets();
    MoveEnemyBullets();
    CheckPlayerBulletCollisions();
    CheckBossBulletCollisions();
    CheckEnemyBulletCollisions();
}

void Game::loop(Renderer & renderer, Controller & controller)
{
    bool BossFire = true; 

    int time1;
    int time2;

    time1 = SDL_GetTicks();
    while(_status)
    {
        time2 = SDL_GetTicks();

        controller.HandleInput(_status,_Player, _player_bullets);

        if(time2 - time1 >1000 )
        {
            time1 = SDL_GetTicks();
            Update(true);
        }
        else 
        {
            Update(false);
        }

        renderer.Render(_Enemy_instances, _player_bullets, _boss_bullets, _enemy_bullets, _Player,_Boss_enemy, _NumberOfEnemies);

        // std::cout<<"Player Health " << _Player.GetHealth()<<"\n";
        // std::cout<<"Boss Health " << _Boss_enemy->GetHealth()<<"\n";

        SDL_Delay(10);
    }
    if(!_Player.LifeStatus())
    {
        std::cout<<"Player Killed \n";
    }
} 