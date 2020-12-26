#include "base.h"

void base_shape::ColorGetter(Color &color)
{
    color.blue = _color.blue;
    color.red = _color.red;
    color.green = _color.green;
}

void base_shape::SetBodyLocation(int &x, int &y) 
{
    _dim.x = x; 
    _dim.y = y; 
}

void base_shape::SetBodySpeed(int speed)
{
    _body_speed = speed;
}

void base_shape::SetBodyDimension(int &width, int &height) 
{
    _dim.w = width; 
    _dim.h = height; 
}

void base_shape::GetBodyLocation(SDL_Point &loc) const 
{
    loc.x = _dim.x;
    loc.y = _dim.y;
}

void base_shape::GetBodySpeed(int &speed)
{
    speed = _body_speed;
}

void base_shape::GetBodyDimension(int &width, int &height)
{
    width = _dim.w;
    height = _dim.h;
}

void base_shape::ReduceLife()
{
    _health--;
    if(_health==0)
    {
        _alive = false;
    }
}

bool base_shape::LifeStatus()
{
    return _alive;
}

int base_shape::GetHealth()
{
    return _health;
}


SDL_Rect * base_shape::GetRect()
{
    SDL_Rect *temp = &(_dim);
    return temp;
}



