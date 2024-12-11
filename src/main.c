#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

int main(int argc, char *argv[])
{
    int cont=1;
    SDL_Event event;
    while (cont) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                cont=0;
                break;
        }
    }
    return 0;
}
