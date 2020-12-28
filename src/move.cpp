#include "move.h"

void Move(boss * Boss, Direction &_boss_direction)
{
    if(Boss->LifeStatus())
    {
        int speed;
        SDL_Point boss_location; 
        Boss->GetBodySpeed(speed);
        Boss->GetBodyLocation(boss_location);
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
        Boss->SetBodyLocation( updated_x, updated_y );
    }
}

void Move(std::vector<enemy*> &Enemies, Direction &_enemy_direction, player &Player)
{
    int speed;
    int horizontal_speed; 
    SDL_Point enemy_location; 
    _enemy_direction = _enemy_direction == Direction::right ? Direction::left : Direction::right; 

    if(Enemies.size()>0)
    {
        for(auto itr:Enemies)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(enemy_location);
            itr->GetBodySpeedHorizontal(horizontal_speed);

            int updated_x = enemy_location.x + _enemy_direction * horizontal_speed;
            int updated_y = enemy_location.y + speed;
            itr->SetBodyLocation( updated_x, updated_y );

            if( updated_y > itr->GetPlayerKillDistance())
            {
                while(Player.LifeStatus())
                {
                    Player.ReduceLife();
                }
            }

        }
    }
}


void MoveBullets(std::vector<bullet*> &Bullets)
{
    int speed;
    SDL_Point bullet_location; 
    
    if(Bullets.size()>0)
    {
        int counter = 0; 
        for(auto itr:Bullets)
        {
            itr->GetBodySpeed(speed);
            itr->GetBodyLocation(bullet_location);

            int updated_x = bullet_location.x;
            int updated_y = bullet_location.y + speed;
            if(updated_y > (ScreenHeight - 10))
            {
                delete itr;
                Bullets.erase(Bullets.begin()+counter);
                break;
            }
            itr->SetBodyLocation( updated_x, updated_y );
            counter++;
        }
    }
}

// void Game::MovePlayerBullets(std::vector<bullet*> &EnemyBullets)
// {
//     int speed;
//     SDL_Point bullet_location; 
    
//     if(EnemyBullets.size()>0)
//     {
//         int counter = 0; 
//         for(auto itr:EnemyBullets)
//         {
//             itr->GetBodySpeed(speed);
//             itr->GetBodyLocation(bullet_location);

//             int updated_x = bullet_location.x;
//             int updated_y = bullet_location.y + speed;
//             if(updated_y > (ScreenHeight - 10))
//             {
//                 delete itr;
//                 EnemyBullets.erase(EnemyBullets.begin()+counter);
//                 break;
//             }
//             itr->SetBodyLocation( updated_x, updated_y );
//             counter++;
//         }
//     }
// }



// void Game::MovePlayerBullets(std::vector<bullet*> &PlayerBullets)
// {
//     int speed;
//     SDL_Point bullet_location; 

//     if(PlayerBullets.size()>0)
//     {
//         int counter = 0; 
//         for(auto itr:PlayerBullets)
//         {
//             itr->GetBodySpeed(speed);
//             itr->GetBodyLocation(bullet_location);

//             int updated_x = bullet_location.x;
//             int updated_y = bullet_location.y - speed;
//             if(updated_y < 10)
//             {
//                 delete itr;
//                 PlayerBullets.erase(PlayerBullets.begin()+counter);
//                 break;
//             }
//             itr->SetBodyLocation( updated_x, updated_y );
//             counter++;
//         }
    
//     }

// }
