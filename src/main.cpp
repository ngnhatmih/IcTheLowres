#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

using namespace std;

SDL_Window *g_window = 0;
SDL_Renderer *g_renderer = 0;

int main(int argc, char *argv[])
{
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) == 0)
    {
        g_window = SDL_CreateWindow("ICTL", 300, 200, 0);
        if (g_window == nullptr)
        {
            cout << "Could not create window" << SDL_GetError() << endl;
        }
        else 
        {
            g_renderer = SDL_CreateRenderer(g_window, 0, 0);
        }
    }
    else { return EXIT_FAILURE; }

    SDL_SetRenderDrawColor(g_renderer, 0, 20, 255, SDL_ALPHA_OPAQUE);

    SDL_Event event;
    bool g_Running = 1;
    while(g_Running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                g_Running = 0;
            }
        }

        SDL_RenderClear(g_renderer);
        SDL_RenderPresent(g_renderer);
    }

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();

    return EXIT_SUCCESS;
}