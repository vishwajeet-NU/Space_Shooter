/// Author: Vishwajeet Karmarkar
/// vishwajeet@u.northwestern.edu

#include "player.h"

player::player()
{
    //green color 
    _color.red = 0x00;
    _color.green = 0x80;
    _color.blue = 0x00;
    _dim.w = 15;
    _dim.h = 15;
    _dim.x = ScreenWidth/2 - _dim.w/2;
    _dim.y = 600;
    _health = 3;
    _body_speed = 2;
    _alive = true; 
}