#include <stdlib.h>
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_image.h"

#pragma comment ( lib, "SDL/libx86/SDL2.lib" )
#pragma comment ( lib, "SDL/libx86/SDL2_image.lib" )
#pragma comment ( lib, "SDL/libx86/SDL2main.lib" )

#define BULLETS 17  
#define MAX_ENEMIES 3

bool EnemyGeneration(int* Bad_Guy)
{
	bool checker = false;
	int Apperance = rand() % 100;
	if (Apperance == 99)
	{
		checker = true;
		*Bad_Guy++;
	}
	return checker;
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

	

	SDL_Rect Shot_Sprite;
	Shot_Sprite.h = 17;
	Shot_Sprite.w = 11;
	Shot_Sprite.y = 145;
	Shot_Sprite.x = 55;

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

	SDL_Rect Enemy[MAX_ENEMIES];
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		Enemy[i].h = 50;
		Enemy[i].w = 50;
		Enemy[i].y = rand() % 431;
		Enemy[i].x = 500;
	}

	SDL_Rect Sprite;
	Sprite.h = 45;
	Sprite.w = 32;
	Sprite.y = 0;
	Sprite.x = 0;

	SDL_Rect Left_Sprite;
	Left_Sprite.h = 47;
	Left_Sprite.w = 32;
	Left_Sprite.y = 47;
	Left_Sprite.x = 0;

	SDL_Rect Right_Sprite;
	Right_Sprite.h = 47;
	Right_Sprite.w = 32;
	Right_Sprite.y = 94;
	Right_Sprite.x = 0;

	SDL_Surface* Character = IMG_Load("Images/Marisa.png");
	SDL_Surface* SBackground = SDL_LoadBMP("Images/Parallax.bmp");
	SDL_Surface* Enemies = SDL_LoadBMP("Images/Tofu.bmp");

	SDL_Texture* Marisa = SDL_CreateTextureFromSurface(renderer, Character);
	SDL_Texture* Shoot = SDL_CreateTextureFromSurface(renderer, Character);
	SDL_Texture* Background = SDL_CreateTextureFromSurface(renderer, SBackground);
	SDL_Texture* Tofu = SDL_CreateTextureFromSurface(renderer, Enemies);

	bool Enemy_Appears = false;
	bool shooting_stars = false;
	bool up_key = false;
	bool down_key = false;
	bool left_key = false;
	bool right_key = false;

	int animation_selector = 0;
	int Frame = 0;
	int Bad_Guy = -1;
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
					left_key = true;  animation_selector = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					right_key = true; animation_selector = 2;
					break;
				case SDL_SCANCODE_SPACE:
					if (event.key.repeat == 0) shooting_stars = true;
					break;
				case SDL_SCANCODE_ESCAPE:
					exit = 0;
					break;
				}
			}
			
			else if (event.type == SDL_KEYUP)
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
					left_key = false; animation_selector = 0;
					break;
				case SDL_SCANCODE_RIGHT:
					right_key = false; animation_selector = 0;
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

		Enemy_Appears = EnemyGeneration(&Bad_Guy);

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

		if (Frame % 4 == 0) { Sprite.x += 32; }
		if (Sprite.x == 224) { Sprite.x = 0; }

		if (Frame % 4 == 0) { Left_Sprite.x += 32; }
		if (Left_Sprite.x == 224) { Left_Sprite.x = 0; }

		if (Frame % 4 == 0) { Right_Sprite.x += 32; }
		if (Right_Sprite.x == 224) { Right_Sprite.x = 0; }

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Background, NULL, &Back[0]);
		SDL_RenderCopy(renderer, Background, NULL, &Back[1]);

		if(animation_selector == 0)	{ SDL_RenderCopy(renderer, Marisa, &Sprite, &Chara); }
		else if(animation_selector == 1) { SDL_RenderCopy(renderer, Marisa, &Left_Sprite, &Chara); }
		else if(animation_selector == 2) { SDL_RenderCopy(renderer, Marisa, &Right_Sprite, &Chara); }

		for (int i = 0; i < BULLETS; i++)
		{
			SDL_RenderCopy(renderer, Shoot, &Shot_Sprite, &Bullet[i]);
		}

 		SDL_RenderPresent(renderer);
		Frame++;
		if (Frame == 60) { Frame = 0; }
	}
	SDL_Quit();
	return(EXIT_SUCCESS);
}