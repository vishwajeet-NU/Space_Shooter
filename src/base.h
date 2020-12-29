#ifndef BASE_H
#define BASE_H
#include "SDL.h"
#include "common.h"
struct Color
{
    int red;
    int green;
    int blue; 
};

class base_shape
{
    public: 
        void ColorGetter(Color &color);
        void SetBodyLocation(int &x, int &y);
        void SetBodyDimension(int &width, int &height);
        void SetBodySpeed(int speed);
        void GetBodyLocation(SDL_Point &loc) const ;        
        void GetBodyDimension(int &width, int &height);
        void GetBodySpeed(int &speed);
        int GetHealth();
        void ReduceLife();
        bool LifeStatus();
        virtual void LevelUp() {}
        SDL_Rect *GetRect();

    protected:
    SDL_Point _location; 
    Color _color;
    SDL_Rect _dim; 
    int _body_speed;
    int _health; 
    bool _alive;

};


#endif