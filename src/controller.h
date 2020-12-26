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
  void HandleInput(bool &running, player &Player_one, std::vector<bullet*> &Player_bullets);
 private:
    void Move(Direction dir, player &Player_one);
    void Shoot(player &Player_one,  std::vector<bullet*> &Player_bullets);
    bool _SpaceLock{false};
    bool _LeftKeyLock{false};
    bool _RightKeyLock{false};
 
};

#endif