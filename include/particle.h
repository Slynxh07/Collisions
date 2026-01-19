#ifndef PARTICLE_H
#define PARTICLE_H

#include "seanMath.h"
#include "SDL2/SDL.h"

typedef struct Particle Particle;

Particle *createParticle(Vector2 pos, Vector2 velocity, int rad);
void destroyParticle(Particle *p);

void updateParticle(Particle *p, int w, int h);
void drawParticle(SDL_Renderer *renderer, Particle *p);


#endif