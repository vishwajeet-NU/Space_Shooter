#include "boss_enemy.h"

boss::boss()
{
    //dark red 
    _color.red = 0x8B;
    _color.green = 0x00;
    _color.blue = 0x00;
    _dim.w = 25;
    _dim.h = 25;
    _dim.x = ScreenWidth/2 - _dim.w/2;
    _dim.y = 20;
    _health = 5;
    _body_speed = 1;
    _alive = true; 

}



