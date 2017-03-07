#include <stdlib.h>
#include "SDL\include\SDL.h"

#pragma comment ( lib, "SDL/libx86/SDL2.lib" )
#pragma comment ( lib, "SDL/libx86/SDL2main.lib" )

#define BULLETS 17  

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Rect r;
	r.h = 100;
	r.w = 100;
	r.x = 0;
	r.y = 0;

	SDL_Rect s[BULLETS];
	for (int i = 0; i < BULLETS; i++)
	{
		s[i].h = 50;
		s[i].w = 50;
		s[i].x = 0;
		s[i].y = -50;
	}

	SDL_Rect t[2];
	t[0].h = 480;
	t[1].h = 480;
	t[0].w = 1240;
	t[1].w = 1240;
	t[0].x = 0;
	t[1].x = 1240;
	t[0].y = 0;
	t[1].y = 0;

	SDL_Surface* Chara = SDL_LoadBMP("Images/Marion.bmp");
	SDL_Surface* Star = SDL_LoadBMP("Images/Star.bmp");
	SDL_Surface* SBackground = SDL_LoadBMP("Images/parallax.bmp");

	SDL_Texture* Marion = SDL_CreateTextureFromSurface(renderer, Chara);
	SDL_Texture* Shoot = SDL_CreateTextureFromSurface(renderer, Star);
	SDL_Texture* Background = SDL_CreateTextureFromSurface(renderer, SBackground);

	bool shooting_stars = false;
	bool up_key = false;
	bool down_key = false;
	bool left_key = false;
	bool right_key = false;

	int bullet_counter = 0;
	int exit = 1;
	while (exit == 1)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					up_key = true;
					break;
				case SDL_SCANCODE_DOWN:
					down_key = true;
					break;
				case SDL_SCANCODE_LEFT:
					left_key = true;
					break;
				case SDL_SCANCODE_RIGHT:
					right_key = true;
					break;
				case SDL_SCANCODE_SPACE:
					if (event.key.repeat == 0) shooting_stars = true;
					break;
				case SDL_SCANCODE_ESCAPE:
					exit = 0;
					break;
				}
			}
			if (up_key) r.y -= 5;
			if (down_key) r.y += 5;
			if (left_key) r.x -= 5;
			if (right_key) r.x += 5;
			if (shooting_stars == true)
			{
				s[bullet_counter].y = r.y + 20;
				s[bullet_counter].x = r.x + 100;
				shooting_stars = false;
				bullet_counter++;
				if (bullet_counter == BULLETS) bullet_counter = 0;
			}

			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					up_key = false;
					break;
				case SDL_SCANCODE_DOWN:
					down_key = false;
					break;
				case SDL_SCANCODE_LEFT:
					left_key = false;
					break;
				case SDL_SCANCODE_RIGHT:
					right_key = false;
					break;
				}
			}
		}
		for (int i = 0; i < BULLETS; i++)
		{
			s[i].x += 10;
		}

		t[0].x -= 31;
		if (t[0].x == -1240)
		{
			t[0].x = 1240;
		}
		t[1].x -= 31;
		if (t[1].x == -1240)
		{
			t[1].x = 1240;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Background, NULL, &t[0]);
		SDL_RenderCopy(renderer, Background, NULL, &t[1]);
		SDL_RenderCopy(renderer, Marion, NULL, &r);
		for (int i = 0; i < BULLETS; i++)
		{
			SDL_RenderCopy(renderer, Shoot, NULL, &s[i]);
		}

		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return(EXIT_SUCCESS);
}