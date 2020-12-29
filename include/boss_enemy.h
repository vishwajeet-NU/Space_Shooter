/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#ifndef BOSS_H
#define BOSS_H

#include "base.h"

class boss : public base_shape
{
    public:
     boss();
      int _points;
      void LevelUp() override;

    private:

};

#endif