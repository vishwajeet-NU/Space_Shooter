#include "create_bullets.h"

void CreateBullets(boss * Boss, std::vector<bullet*> &BossBullets)
{
    if(Boss->LifeStatus())
    {
      bullet *Bullet_B = new bullet((*Boss));
      SDL_Point location;
      int width, height;
      Boss->GetBodyDimension(width,height);
      Boss->GetBodyLocation(location);
      int loc1 = location.x + width/2;
      int loc2 = location.y + height;
      Bullet_B->SetBodyLocation(loc1,loc2);
      BossBullets.emplace_back(Bullet_B);
    }
}

void CreateBullets(std::vector<enemy*> &Enemies, std::vector<bullet*> &EnemyBullets,std::mt19937 engine, int _NumberOfEnemies)
{
    if(Enemies.size()>0)
    {
        std::uniform_int_distribution<int> random_enemy(0,_NumberOfEnemies-1);
        int index = random_enemy(engine);
        enemy *source_enemy = Enemies[index];
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
            EnemyBullets.emplace_back(Bullet_E);
        }
    }
}