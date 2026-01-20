#ifndef SEANMATH_H
#define SEANMATH_H

typedef struct Vector2
{
    float x, y;
} Vector2;

Vector2 addVector2(Vector2 v1, Vector2 v2);
float calcDotProduct(Vector2 v1, Vector2 v2);
Vector2 normaliseVector(Vector2 v);

#endif