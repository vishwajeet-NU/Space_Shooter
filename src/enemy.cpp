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
    _body_speed = 2;
    _xaxisSpeed = 15;
    _points = 10;
    _playerKillDistance = (ScreenHeight -80);    

    _alive = true; 
}

void enemy::GetBodySpeedHorizontal(int &speed)
{
    speed = _xaxisSpeed ;
}

int enemy::GetPlayerKillDistance()
{
    return _playerKillDistance;
}
