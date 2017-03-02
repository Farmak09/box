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
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 50;
	r.h = 50;
	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
	
	SDL_RenderPresent(renderer);
	int x = 0;
	int y = 0;
	int i = 1;
	while (i == 1) 
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
				{
					y -= 5;
					break;
				}
				case SDL_SCANCODE_DOWN:
				{
					y += 5;
					break;
				}
				case SDL_SCANCODE_LEFT:
				{
					x -= 5;
					break;
				}
				case SDL_SCANCODE_RIGHT:
				{
					x += 5;
					break;
				}
				case SDL_SCANCODE_ESCAPE:
				{
					i = 0;
					break;
				}
				default:
				{
					i = 1;
				}
				}		
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
		SDL_RenderClear(renderer);
		r.x = x;
		r.y = y;
		SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return(EXIT_SUCCESS);
}