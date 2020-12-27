#include "bullet.h"

bullet::bullet(enemy &E)
{
    Color col;
    E.ColorGetter(col);
    _color.red = col.red;
    _color.green = col.green;
    _color.blue = col.blue;
    _dim.w = 3;
    _dim.h = 5;
    _health = 1;
    _body_speed = 1;
    _alive = true; 

}
bullet::bullet(player &P)
{
    Color col;
    P.ColorGetter(col);
    _color.red = col.red;
    _color.green = col.green;
    _color.blue = col.blue;
    _dim.w = 3;
    _dim.h = 6;
    _health = 1;
    _body_speed = -2;
    _alive = true; 

}
bullet::bullet(boss &B)
{
    Color col;
    B.ColorGetter(col);
    _color.red = col.red;
    _color.green = col.green;
    _color.blue = col.blue;
    _dim.w = 4;
    _dim.h = 8;
    _health = 1;
    _body_speed = 1;
    _alive = true; 
    
}
