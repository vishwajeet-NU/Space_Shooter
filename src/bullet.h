#ifndef BULLET_H
#define BULLET_H
#include "base.h"
#include "player.h"
#include "enemy.h"
#include "boss_enemy.h"

class bullet : public base_shape
{
    public: 
        bullet(enemy &E);
        bullet(player &P);
        bullet(boss &B);
};


#endif