#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "player.h"
#include "common.h"
#include "bullet.h"

enum Direction
{
    left=-1, right= 1
};

class Controller {
 public:
  void HandleInput(bool &running, player &Player_one, std::vector<bullet*> &Player_bullets) const;
 private:
    void Move(Direction dir, player &Player_one) const;
    void Shoot(player &Player_one,  std::vector<bullet*> &Player_bullets) const;
 
};

#endif