#include "game.h"
#include <memory>
#include <thread>



Game::Game():_NumberOfEnemies(4), _EnemyStart_x(30), _EnemyStart_y(100),_EnemyGapSize_x(80), _EnemyGapSize_y(50), _status(true), engine(dev()), _score{0}, _victory{false}, _level{1}
{

    int x_location = _EnemyStart_x;
    int y_location = _EnemyStart_y;

    _boss_direction = Direction::left;
    _enemy_direction = Direction::right;
    _Boss_enemy = new boss; 

    CreateEnemies(_Enemy_instances,_NumberOfEnemies,y_location, x_location, _EnemyGapSize_y, _EnemyGapSize_x, _EnemyStart_x);
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
        Move(_Enemy_instances,_enemy_direction,_Player);
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
    SDL_Color col = _backgroundcolor.Black;
    int time1;
    int time2;
    int no_of_enemies = _NumberOfEnemies;

    time1 = SDL_GetTicks();
    while(_status && _Player.LifeStatus())
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

        renderer.Render(_Enemy_instances, _player_bullets, _boss_bullets, _enemy_bullets, _Player,_Boss_enemy, _NumberOfEnemies, _score, col);
        if(!_Boss_enemy->LifeStatus() && _Enemy_instances.size()==0)
        {
            if(_level ==11)
            {
                _victory= true;
                break;    
            }
            renderer.Render("Level Up !!",_backgroundcolor.Green);
            col = (col.r == _backgroundcolor.Black.r && col.g == _backgroundcolor.Black.g && col.b == _backgroundcolor.Black.b)  ? _backgroundcolor.Brown : _backgroundcolor.Black;
            SDL_Delay(500);
            _Boss_enemy = new boss; 
            _Boss_enemy->LevelUp();
            _NumberOfEnemies = no_of_enemies;
            CreateEnemies(_Enemy_instances,_NumberOfEnemies,_EnemyStart_y, _EnemyStart_x, _EnemyGapSize_y, _EnemyGapSize_x, _EnemyStart_x);

            for(auto itr:_Enemy_instances)
            {
                itr->LevelUp();
            }

        }

        SDL_Delay(10);
    }
    _status = true; 
    while(_status && !_Player.LifeStatus())
    {
        controller.HandleInput(_status);
        renderer.Render("Game Over !!",_backgroundcolor.Blue);
    }
    while(_status && _victory)
    {
        controller.HandleInput(_status);
        renderer.Render("You Won !!         Score = " + std::to_string(_score),_backgroundcolor.Black);

    }
} 