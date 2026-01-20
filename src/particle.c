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
    Vector2 distVec;
    distVec.x = p2->pos.x - p1->pos.x;
    distVec.y = p2->pos.y - p1->pos.y;
    float radii = p1->rad + p2->rad;

    return (distVec.x * distVec.x + distVec.y * distVec.y) <= (radii * radii);
}

void handleCollision(Particle* p1, Particle* p2)
{
    Vector2 distVec, nDistVec, nTangentVec;
    distVec.x = p1->pos.x - p2->pos.x;
    distVec.y = p1->pos.y - p2->pos.y;

    float distSq = distVec.x * distVec.x + distVec.y * distVec.y;
    float radii = p1->rad + p2->rad;

    if (distSq == 0.0f)
    {
        distVec.x = 1.0f;
        distVec.y = 0.0f;
        distSq = 1.0f;
    }

    float distMag = sqrt(distSq);
    float overlap = radii - distMag;

    nDistVec.x = distVec.x / distMag;
    nDistVec.y = distVec.y / distMag;

    float correction = overlap * 0.5f;

    p1->pos.x += nDistVec.x * correction;
    p1->pos.y += nDistVec.y * correction;

    p2->pos.x -= nDistVec.x * correction;
    p2->pos.y -= nDistVec.y * correction;

    nTangentVec.x = -nDistVec.y;
    nTangentVec.y = nDistVec.x;

    float v1n, v1t, v2n, v2t;
    v1n = p1->velocity.x * nDistVec.x + p1->velocity.y * nDistVec.y;
    v1t = p1->velocity.x * nTangentVec.x + p1->velocity.y * nTangentVec.y;

    v2n = p2->velocity.x * nDistVec.x + p2->velocity.y * nDistVec.y;
    v2t = p2->velocity.x * nTangentVec.x + p2->velocity.y * nTangentVec.y;

    Vector2 v1 = {v2n, v1t};
    Vector2 v2 = {v1n, v2t};

    p1->velocity.x = v1.x * nDistVec.x + v1.y * nTangentVec.x;
    p1->velocity.y = v1.x * nDistVec.y + v1.y * nTangentVec.y;

    p2->velocity.x = v2.x * nDistVec.x + v2.y * nTangentVec.x;
    p2->velocity.y = v2.x * nDistVec.y + v2.y * nTangentVec.y;
}