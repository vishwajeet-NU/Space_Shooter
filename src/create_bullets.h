#ifndef CREATEBULLETS_H
#define CREATEBULLETS_H

#include "boss_enemy.h"
#include "enemy.h"
#include "bullet.h"
#include <vector>
#include "SDL.h"
#include "common.h"
#include <random>


void CreateBullets(boss * Boss, std::vector<bullet*> &BossBullets);
void CreateBullets(std::vector<enemy*> &Enemies, std::vector<bullet*> &EnemyBullets,std::mt19937 &engine, int _NumberOfEnemies);


#endif