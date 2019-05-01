#include "sdlGameLoop.h"
#include "world.h"

int main(int argc, char **argv)
{
    world mainWorld;
    SdlGame sg;
    sg.sdlLoop(mainWorld);
    return 0;
}