#include "particle.h"
#include <stdlib.h>
#include <math.h>

typedef struct Particle
{
    Vector2 pos, velocity;
    int rad;
} Particle;


Particle *createParticle(Vector2 pos, Vector2 velocity, int rad)
{
    Particle *p = malloc(sizeof(Particle));
    p->pos = pos;
    p->velocity = velocity;
    p->rad = rad;
    return p;
}

void destroyParticle(Particle *p)
{
    free(p);
}

void drawParticle(SDL_Renderer *renderer, Particle *p)
{
    for (int y = -p->rad; y <= p->rad; y++)
    {
        int dx = (int)sqrt(p->rad * p->rad - y * y);
        SDL_RenderDrawLine(renderer, p->pos.x - dx, p->pos.y + y, p->pos.x + dx, p->pos.y + y);
    }
}

void updateParticle(Particle *p, int w, int h)
{
    p->pos = addVector2(p->pos, p->velocity);
    if (p->pos.x + p->rad >= w)
    {
        p->pos.x = w - p->rad;
        p->velocity.x *= -1;
    }
    if (p->pos.x - p->rad <= 0)
    {
        p->pos.x = p->rad;
        p->velocity.x *= -1;
    }
    if (p->pos.y - p->rad <= 0)
    {
        p->pos.y = p->rad;
        p->velocity.y *= -1;
    }
    if (p->pos.y + p->rad >= h)
    {
        p->pos.y = h - p->rad;
        p->velocity.y *= -1;
    }
}

bool checkCollision(Particle *p1, Particle *p2)
{
    float dx = p2->pos.x - p1->pos.x;
    float dy = p2->pos.y - p1->pos.y;
    float radii = p1->rad + p2->rad;

    return (dx * dx + dy * dy) <= (radii * radii);
}

void handleCollision(Particle* p1, Particle* p2)
{
    float dx = p1->pos.x - p2->pos.x;
    float dy = p1->pos.y - p2->pos.y;

    float distSq = dx*dx + dy*dy;
    float radii = p1->rad + p2->rad;

    if (distSq == 0.0f)
    {
        dx = 1.0f;
        dy = 0.0f;
        distSq = 1.0f;
    }

    float dist = sqrt(distSq);
    float overlap = radii - dist;

    float nx = dx / dist;
    float ny = dy / dist;

    float correction = overlap * 0.5f;

    p1->pos.x += nx * correction;
    p1->pos.y += ny * correction;

    p2->pos.x -= nx * correction;
    p2->pos.y -= ny * correction;
}
