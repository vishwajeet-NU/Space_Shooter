#include "enemy.h"

enemy::enemy()
{
    // yellow    
    _color.red = 0xFF;
    _color.green = 0xFF;
    _color.blue = 0x00;
    _dim.w = 15;
    _dim.h = 15;
    _health = 1;
    _body_speed = 1;
    _xaxisSpeed = 15;
    _alive = true; 
}

void enemy::GetBodySpeedHorizontal(int &speed)
{
    speed = _xaxisSpeed ;
}
