/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "player.h"
#include "common.h"
#include "bullet.h"


class Controller {
 public:
  void HandleInput(bool &running, player &Player_one, std::vector<bullet*> &Player_bullets);
  void HandleInput(bool &running);

 private:
    void Move(Direction dir, player &Player_one);
    void Shoot(player &Player_one,  std::vector<bullet*> &Player_bullets);
    bool _SpaceLock{false};
    bool _LeftKeyLock{false};
    bool _RightKeyLock{false};
 
};

#endif