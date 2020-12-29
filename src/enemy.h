/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#ifndef ENEMY_H
#define ENEMY_H

#include "base.h"
#include <vector>
#include "common.h"

class enemy : public base_shape
{
    public:
        enemy();
        void GetBodySpeedHorizontal(int &speed);
        int GetPlayerKillDistance();
        int _points;
        void LevelUp() override;
    private:

        int _xaxisSpeed;
        int _playerKillDistance;    
};

#endif