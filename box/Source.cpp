#include <stdlib.h>
#include "SDL\include\SDL.h"

#pragma comment ( lib, "SDL/libx86/SDL2.lib" )
#pragma comment ( lib, "SDL/libx86/SDL2main.lib" )


int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Rect r;
	r.x = 215;
	r.y = 125;
	r.w = 200;
	r.h = 200;

	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);

	for (;;) 
	{

	}

	SDL_Quit();
	return(EXIT_SUCCESS);
}