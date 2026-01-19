#ifndef SEANMATH_H
#define SEANMATH_H

typedef struct Vector2
{
    float x, y;
} Vector2;

typedef struct Vector3
{
    float x, y, z;
} Vector3;

Vector2 addVector2(Vector2 v1, Vector2 v2);
Vector3 addVector3(Vector3 v1, Vector3 v2);

#endif