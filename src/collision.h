/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#ifndef COLLISION_H
#define COLLISION_H

#include "boss_enemy.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

void CheckBulletCollisions(boss * Boss, std::vector<enemy*> &EnemyInstances, std::vector<bullet*> &Bullets, int &_score,  int &_NumberOfEnemies);
void CheckBulletCollisions(player &Player, std::vector<bullet*> &Bullets, bool &_status);


#endif