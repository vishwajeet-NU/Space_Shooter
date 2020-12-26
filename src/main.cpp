#include <iostream>
#include "renderer.h"
#include "common.h"
#include "game.h"
#include "controller.h"

int main ()

{
    Renderer renderer(ScreenWidth, ScreenHeight, GridWidth, GridHeight);
    Game mygame;
    Controller controller; 
    mygame.loop(renderer, controller);

    return 0;
}
