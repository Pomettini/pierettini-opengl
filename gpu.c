#include <SDL2/SDL.h>

typedef int (*adder_signature)(int a, int b);

int main(int argc, char **argv)
{
    void *handle = SDL_LoadObject("plugin.so");
    if (!handle)
    {
        SDL_Log("Error loading library_ %s", SDL_GetError());
        return -1;
    }

    adder_signature adder = (adder_signature)SDL_LoadFunction(handle, "adder");
    if (!adder)
    {
        SDL_Log("Error loading symbol: %s", SDL_GetError());
        return -1;
    }

    SDL_Log("Result is %d", adder(3, 4));

    return 0;
}