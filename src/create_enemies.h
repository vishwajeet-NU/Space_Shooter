#ifndef CREATEENEMIES_H
#define CREATEENEMIES_H

#include "boss_enemy.h"
#include "enemy.h"

void CreateEnemies(std::vector<enemy*> &EnemyInstances, int &NumberOfEnemies, int y_location, int x_location, int EnemyGapSizeY, int EnemyGapSizex, int EnemyStartx);


#endif