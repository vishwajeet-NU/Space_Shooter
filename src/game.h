#ifndef GAME_H
#define GAME_H

#include <random>
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "boss_enemy.h"
#include "controller.h"

class Game
{
public:
    void loop( Renderer & renderer, Controller & controller );
    Game();
    ~Game();
private: 
    void Update(bool move_enemies);
    void MoveBoss();
    void MoveEnemies();   
    void MovePlayerBullets();
    void MoveBossBullets();
    void MoveEnemyBullets();
    void CheckPlayerBulletCollisions();
    void CheckBossBulletCollisions();
    void CheckEnemyBulletCollisions();
    void CreateBossBullet();
    void CreateEnemyBullet();


    std::vector<enemy*> _Enemy_instances;
    player _Player;
    boss * _Boss_enemy;
    Direction _boss_direction; 
    Direction _enemy_direction; 
 
    std::vector<bullet*> _player_bullets;
    std::vector<bullet*> _boss_bullets;
    std::vector<bullet*> _enemy_bullets;

    std::random_device dev;
    std::mt19937 engine;

    int _NumberOfEnemies; 
    int _EnemyStart_x;
    int _EnemyStart_y;
    int _EnemyGapSize_x; 
    int _EnemyGapSize_y; 

    bool _status;

};



#endif