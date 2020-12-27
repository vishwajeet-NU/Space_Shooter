#include "game.h"
#include <memory>
#include <thread>



Game::Game():_NumberOfEnemies(36), _EnemyStart_x(30), _EnemyStart_y(100),_EnemyGapSize_x(80), _EnemyGapSize_y(50), _status(true), engine(dev()), _score{0}, _level{1}
{
    int counter_x = 0; 
    int counter_y = 0;

    int x_location = _EnemyStart_x;
    int y_location = _EnemyStart_y;

    _boss_direction = Direction::left;
    _enemy_direction = Direction::right;
    
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
        for(auto itr:_Enemy_instances)
        {
            delete itr;
        }
    }
    if(_player_bullets.size()>0)
    {
        for (auto itr:_player_bullets)
        {
            delete itr;
        }
    }
    if(_boss_bullets.size()>0)
    {
        for (auto itr:_boss_bullets)
        {
            delete itr;
        }
    }

    delete _Boss_enemy;
}


void Game::Update(bool move_enemies)
{
    Move(_Boss_enemy,_boss_direction);
    if(move_enemies)
    {
        Move(_Enemy_instances,_enemy_direction);
        CreateBullets(_Boss_enemy,_boss_bullets);
        CreateBullets(_Enemy_instances,_enemy_bullets,engine,_NumberOfEnemies);
    }
    MoveBullets(_player_bullets);
    MoveBullets(_boss_bullets);
    MoveBullets(_enemy_bullets);

    CheckBulletCollisions(_Boss_enemy,_Enemy_instances,_player_bullets,_score,_NumberOfEnemies);
    CheckBulletCollisions(_Player,_boss_bullets,_status);
    CheckBulletCollisions(_Player,_enemy_bullets,_status);
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

        renderer.Render(_Enemy_instances, _player_bullets, _boss_bullets, _enemy_bullets, _Player,_Boss_enemy, _NumberOfEnemies, _score);
        SDL_Delay(10);
    }
    if(!_Player.LifeStatus())
    {
        std::cout<<"Player Killed \n";
    }
} 