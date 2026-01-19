#ifndef PARTICLE_H
#define PARTICLE_H

#include "seanMath.h"
#include "SDL2/SDL.h"
#include <stdbool.h>

typedef struct Particle Particle;

Particle *createParticle(Vector2 pos, Vector2 velocity, int rad);
void destroyParticle(Particle *p);

void updateParticle(Particle *p, int w, int h);
void drawParticle(SDL_Renderer *renderer, Particle *p);
bool checkCollision(Particle *p1, Particle *p2);
void handleCollision(Particle *p1, Particle *p2);


#endif