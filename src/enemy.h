#ifndef ENEMY_H
#define ENEMY_H

#include "base.h"
#include <vector>

class enemy : public base_shape
{
    public:
        enemy();
        void GetBodySpeedHorizontal(int &speed);

    private:
        int _xaxisSpeed; 
  
};



#endif