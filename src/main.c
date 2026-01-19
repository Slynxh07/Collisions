#include "SDL2/SDL.h"
#include "seanMath.h"
#include "particle.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

#define NUM_PARTICLES 15

void initParticles();
void updateParticles();
void drawParticles();
void cleanUp();
int getRand();

Particle *particles[NUM_PARTICLES];
SDL_Window *window;
SDL_Renderer *renderer;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Collisions", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    initParticles();
    int running = 1;
    SDL_Event event;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        updateParticles();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawParticles();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cleanUp();
    SDL_Quit();
}

void initParticles()
{
    srand(time(NULL));
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        int r = getRand(5, 15);
        Particle *p = createParticle((Vector2){ getRand(r, WIDTH - r), getRand(r, HEIGHT - r) }, (Vector2){5, 4}, r);
        particles[i] = p;
    }
}

void updateParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        updateParticle(particles[i], WIDTH, HEIGHT);
    }
}

void drawParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        drawParticle(renderer, particles[i]);
    }
}

void cleanUp()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        destroyParticle(particles[i]);
    }
}

int getRand(int min, int max)
{
    return rand() % (max - min + 1) + min;
}