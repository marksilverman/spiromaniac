#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>

class spiro
{
public:
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	int x_zero = SCREEN_WIDTH / 2;
	int y_zero = SCREEN_HEIGHT / 2;
	int radius1 = 3;
	int radius2 = 4;
	int phase1 = 0;
	int phase2 = 0;
	double resolution = 5.0;
	double height = 0.5;
	double changeInHeight = 0.2;
	double factor = 50.0;
	int r, g, b;

	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRenderer = nullptr;

	spiro()
	{
		SDL_Init(SDL_INIT_VIDEO);
		gWindow = SDL_CreateWindow("spiro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		srand(time(NULL));
		this->r = rand() % 255;
		this->g = rand() % 255;
		this->b = rand() % 255;
	}

	void color()
	{
		this->r += 1;
		this->g += 1;
		this->b += 1;
		if (this->r > 255) this->r -= 255;
		if (this->g > 255) this->g -= 255;
		if (this->b > 255) this->b -= 255;
	}

	void draw(int x1, int y1, int x2, int y2)
	{
		int thickness = 4;
		//color();
		SDL_SetRenderDrawColor(gRenderer, this->r, this->g, this->b, 0xff);
		for (int i = 0; i < thickness; i++)
		{
			SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
			SDL_RenderDrawLine(gRenderer, x1 + i, y1, x2 + i, y2);
			SDL_RenderDrawLine(gRenderer, x1 - i, y1, x2 - i, y2);
			SDL_RenderDrawLine(gRenderer, x1, y1 + i, x2, y2 + i);
			SDL_RenderDrawLine(gRenderer, x1, y1 - i, x2, y2 - i);
			SDL_RenderDrawLine(gRenderer, x1 + i, y1 + i, x2 + i, y2 + i);
			SDL_RenderDrawLine(gRenderer, x1 - i, y1 - i, x2 - i, y2 - i);
		}
	}

	void go()
	{
		bool stop = false;
		SDL_Event e;
		int radius;

		while (true)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xcc, 0xdd, 0xee, 0xFF);
			SDL_RenderClear(gRenderer);
			int x = 0, y = 0, radius = radius1 - radius2;
			int starting_x = 0, starting_y = 0, oldx = x_zero, oldy = y_zero;
			bool tooBig = false;

			for (int big_angle = 0; big_angle < (int)(resolution * 40 * 2 * M_PI); big_angle++)
			{
				double angle = (double) big_angle / resolution;
				auto rad = radius * factor;
				auto rad2 = radius2 * factor;
				auto h = height * factor;
				x =  (int)(x_zero + rad * cos(angle));
				x += (int)(h * cos(angle * rad / rad2));

				y = (int)(y_zero + rad * sin(angle));
				y -= (int)(h * sin(angle * rad / rad2));

				if (y <= -50 || y >= SCREEN_HEIGHT + 50)
					tooBig = true;

				if (starting_x)
				{
					draw(x, y, oldx, oldy);
				}
				else
				{
					starting_x = x;
					starting_y = y;
				}
				oldx = x;
				oldy = y;
				if (big_angle > 300 and x == starting_x and y == starting_y)
					break;
			}
			SDL_RenderPresent(gRenderer);

			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.scancode == SDL_SCANCODE_C)
					{
						this->r = rand() % 255;
						this->g = rand() % 255;
						this->b = rand() % 255;
					}
					else if (e.key.keysym.scancode == SDL_SCANCODE_P)
					{
						while (SDL_PollEvent(&e) == 0 || e.type != SDL_KEYDOWN)
						{ }
					}
					else
					{
						height = 0.5;
						changeInHeight = 0.2;
						switch (e.key.keysym.scancode)
						{
						case SDL_SCANCODE_R: // reset
							break;
						case SDL_SCANCODE_Q: // quit
							stop = true; break;
						case SDL_SCANCODE_UP:
							radius1 += 1; break;
						case SDL_SCANCODE_DOWN:
							radius1 -= 1; break;
						case SDL_SCANCODE_LEFT:
							radius2 -= 1; break;
						case SDL_SCANCODE_RIGHT:
							radius2 += 1; break;
						}
						printf("\nradius1: %d\n", radius1);
						printf("radius2: %d\n", radius2);
					}
				}
				else if (e.type == SDL_QUIT)
				{
					stop = true;
				}
			}
			else
			{
				if (tooBig)
				{
					tooBig = false;
					changeInHeight *= -1;
				}
				height += changeInHeight;
			}
			if (stop)
				break;
			//SDL_Delay(10);

		}

		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
	}
};

int main(int argc, char* args[])
{
	spiro s;
	s.go();
	return 0;
}