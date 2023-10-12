#ifdef _WIN32
#include<SDL.h>
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <list>
#include <ctime>

#include "vector2.h"
#include "pointGenerator.h"
#include "triangle.h"
#include "delaunayTriangulation.h"

using namespace std;

#define NUMBER_OF_POINTS 100
#define RADIUS 40.f

#define WIDTH 1280
#define HEIGHT 720
#define HEIGHT_OFFSET 10

#define RECT_SIZE (HEIGHT - HEIGHT_OFFSET * 2)
#define WIDTH_OFFSET ((WIDTH - RECT_SIZE) / 2)

#define FPS 60

SDL_Point toSDLPoint(Vector2 vec, float circleRadius) {
	SDL_Point p{};
	float multiplier = (float)RECT_SIZE / (circleRadius * 2);
	p.x = (int)((vec.x + circleRadius) * multiplier) + WIDTH_OFFSET;
	p.y = (int)((-vec.y + circleRadius) * multiplier) + HEIGHT_OFFSET;
	return p;
}

int renderTriangulation(Vector2* points, unsigned numberOfPoints, float circleRadius, std::list<TriangleC> triangles) {
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	renderer = SDL_CreateRenderer(window, 0, 0);

	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		system("pause");
		// End the program
		return 1;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (unsigned i = 0; i < numberOfPoints; i++) {
		SDL_Point p = toSDLPoint(points[i], circleRadius);
		SDL_Rect r{ p.x - 3, p.y - 3, 7, 7 };
		SDL_RenderFillRect(renderer, &r);
	}

	for (std::list<TriangleC>::iterator i = triangles.begin(); i != triangles.end(); i++) {
		Edge edges[3];
		i->triangle.getEdges(edges);
		for (int tIndex = 0; tIndex < 3; tIndex++) {
			SDL_Point a = toSDLPoint(edges[tIndex].x, circleRadius);
			SDL_Point b = toSDLPoint(edges[tIndex].y, circleRadius);
			SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
		}

		//SDL_RenderDrawLine(renderer, )
	}

	//toSDLPoint(Vector2{}, 1.f);

	SDL_RenderPresent(renderer);

	bool keep_window_open = true;
	SDL_Event e;
	Uint32 waittime = 1000.0f / FPS;
	Uint32 framestarttime = 0;
	Sint32 delaytime;
	while (keep_window_open)
	{
		while (SDL_PollEvent(&e) > 0)
		{
			if (e.window.event == SDL_WINDOWEVENT_CLOSE)
				switch (e.type)
				{
				case SDL_QUIT:
					keep_window_open = false;
					break;
				}
			//SDL_RenderPresent(renderer);
		}

		delaytime = waittime - (SDL_GetTicks() - framestarttime);
		if (delaytime > 0) SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();
	}

	std::cout << "Cleaning\n";

	SDL_DestroyRenderer(renderer);
	// Destroy the window. This will also destroy the surface
	SDL_DestroyWindow(window);

	// Quit SDL
	SDL_Quit();

	return 0;
}

int main(int argc, char** args) {

	std::srand(std::time(0));

	//Vector2 v(0, 0);
	//SDL_Point p = toSDLPoint(v, RADIUS);
	//std::cout << p.x << " " << p.y << "\n";

	Vector2* vectors = generatePointsInCircle(RADIUS, NUMBER_OF_POINTS, 2.5f);

	std::list<TriangleC> triangulation = triangulate(vectors, NUMBER_OF_POINTS);

	for (unsigned i = 0; i < NUMBER_OF_POINTS; i++) {
		std::cout << "[" << vectors[i].x << "," << vectors[i].y << "]" << std::endl;
	}

	renderTriangulation(vectors, NUMBER_OF_POINTS, RADIUS, triangulation);

	free(vectors);
	return 0;
}
