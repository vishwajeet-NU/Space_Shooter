#include "collision.h"


void CheckBulletCollisions(boss * Boss, std::vector<enemy*> &EnemyInstances, std::vector<bullet*> &Bullets, int &_score, int &_NumberOfEnemies)
{
    if(Bullets.size()>0)
    {
        int bullet_counter = 0;

        for(auto itr:Bullets)
        {
            int enemy_counter = 0;
            bool bullet_ = true;

            SDL_Rect *bul = itr->GetRect();
            for(auto it:EnemyInstances)
            {
                SDL_Rect *ene = it->GetRect();
                SDL_bool collide = SDL_HasIntersection(bul,ene);
                if(collide)
                {
                    it->ReduceLife();
                    delete itr;
                    bullet_ = false;
                    Bullets.erase(Bullets.begin()+bullet_counter);

                    if(!it->LifeStatus())
                    {
                        delete it;
                        EnemyInstances.erase(EnemyInstances.begin()+enemy_counter);
                        _NumberOfEnemies--;
                        _score = _score + it->_points; 
                        break; 
                    }
                    collide = SDL_FALSE; 
                }  

                enemy_counter ++;               
            }
            if(bullet_ && Boss->LifeStatus() )
            {

                SDL_Rect *bos = Boss->GetRect();
                SDL_bool collide = SDL_HasIntersection(bul,bos);
                if(collide)
                {
                    Boss->ReduceLife();
                    Bullets.erase(Bullets.begin()+bullet_counter);
                    delete itr;
                    if(!Boss->LifeStatus())
                    {
                        _score = _score + Boss->_points; 

                    }                
                }
            }

            bullet_counter++;
        
        }
    }

}

void CheckBulletCollisions(player &Player, std::vector<bullet*> &Bullets, bool &_status)
{
    if(Bullets.size()>0)
    {
        int bullet_counter = 0;
        for(auto itr:Bullets)
        {
            SDL_Rect *bul = itr->GetRect();
            SDL_Rect *user = Player.GetRect();
            SDL_bool collide = SDL_HasIntersection(bul,user);
            if(collide)
            {
                Player.ReduceLife();
                delete itr;
                Bullets.erase(Bullets.begin()+bullet_counter);

                if(!Player.LifeStatus())
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
