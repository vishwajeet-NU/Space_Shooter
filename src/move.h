#ifndef MOVE_H
#define MOVE_H

#include "boss_enemy.h"
#include "bullet.h"
#include "enemy.h"
#include <vector>
#include "SDL.h"
#include "common.h"


void Move(boss * Boss, Direction &_boss_direction);
void Move(std::vector<enemy*> &Enemies, Direction &_enemy_direction, player &Player);

void MoveBullets(std::vector<bullet*> &Bullets);

#endif