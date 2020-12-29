/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#include "create_enemies.h"

void CreateEnemies(std::vector<enemy*> &EnemyInstances, int &NumberOfEnemies, int y_location, int x_location, int EnemyGapSizeY, int EnemyGapSizex, int EnemyStartx)
{
    int counter_x = 0; 
    int counter_y = 0;


    while(counter_y<sqrt(NumberOfEnemies))
    {
        while (counter_x<sqrt(NumberOfEnemies))
        {
            enemy *single_enemy = new enemy;
            x_location = x_location + EnemyGapSizex; 
            single_enemy->SetBodyLocation(x_location, y_location);
            EnemyInstances.emplace_back(single_enemy);
            counter_x ++;
        }        

        y_location = y_location + EnemyGapSizeY; 
        x_location = EnemyStartx;

        counter_x = 0; 
        counter_y++;
    }

}
