#include "sdlGameLoop.h"
#include "world.h"

int main(void)
{
    world mainWorld;
    SdlGame sg;
    sg.sdlLoop(mainWorld);
    return 0;
}