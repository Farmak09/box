#include <stdlib.h>
#include "SDL\include\SDL.h"

#pragma comment ( lib, "SDL/libx86/SDL2.lib" )
#pragma comment ( lib, "SDL/libx86/SDL2main.lib" )

#define BULLETS 17  

void EnemyGeneration()
{
	bool Enemy_Appears = false;
	int Apperance = rand() % 100;
	if (Apperance == 99)
	{
		Enemy_Appears = true;
	}
}

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Rect Chara;
	Chara.h = 100;
	Chara.w = 100;
	Chara.x = 0;
	Chara.y = 0;

	SDL_Rect Bullet[BULLETS];
	for (int i = 0; i < BULLETS; i++)
	{
		Bullet[i].h = 50;
		Bullet[i].w = 50;
		Bullet[i].x = 0;
		Bullet[i].y = -50;
	}

	SDL_Rect Back[2];
	Back[0].h = 480;
	Back[1].h = 480;
	Back[0].w = 1186;
	Back[1].w = 1186;
	Back[0].x = 0;
	Back[1].x = 1186;
	Back[0].y = 0;
	Back[1].y = 0;

	SDL_Rect Enemy;
	Enemy.h = 100;
	Enemy.w = 100;
	Enemy.y = rand() % 


	SDL_Surface* Chara = SDL_LoadBMP("Images/Marion.bmp");
	SDL_Surface* Star = SDL_LoadBMP("Images/Star.bmp");
	SDL_Surface* SBackground = SDL_LoadBMP("Images/Parallax.bmp");

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
					if (event.key.repeat == 0) up_key = true;
					break;
				case SDL_SCANCODE_DOWN:
					if (event.key.repeat == 0) down_key = true;
					break;
				case SDL_SCANCODE_LEFT:
					if (event.key.repeat == 0) left_key = true;
					break;
				case SDL_SCANCODE_RIGHT:
					if (event.key.repeat == 0) right_key = true;
					break;
				case SDL_SCANCODE_SPACE:
					if (event.key.repeat == 0) shooting_stars = true;
					break;
				case SDL_SCANCODE_ESCAPE:
					exit = 0;
					break;
				}
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

			if (up_key) Chara.y -= 10; if (Chara.y < 0) Chara.y = 0;
			if (down_key) Chara.y += 10; if (Chara.y > 380) Chara.y = 380;
			if (left_key) Chara.x -= 10; if (Chara.x < 0) Chara.x = 0;
			if (right_key) Chara.x += 10; if (Chara.x > 540) Chara.x = 540;
			if (shooting_stars == true)
			{
				Bullet[bullet_counter].y = Chara.y + 20;
				Bullet[bullet_counter].x = Chara.x + 100;
				shooting_stars = false;
				bullet_counter++;
				if (bullet_counter == BULLETS) bullet_counter = 0;
			}
		}
		for (int i = 0; i < BULLETS; i++)
		{
			Bullet[i].x += 10;
		}

		EnemyGeneration();

		Back[0].x -= 2;
		if (Back[0].x <= -1186)
		{
			Back[0].x = 1186;
		}
		Back[1].x -= 2;
		if (Back[1].x <= -1186)
		{
			Back[1].x = 1186;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Background, NULL, &Back[0]);
		SDL_RenderCopy(renderer, Background, NULL, &Back[1]);
		SDL_RenderCopy(renderer, Marion, NULL, &Chara);
		for (int i = 0; i < BULLETS; i++)
		{
			SDL_RenderCopy(renderer, Shoot, NULL, &Bullet[i]);
		}

 		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return(EXIT_SUCCESS);
}