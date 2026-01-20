#include "seanMath.h"
#include <math.h>

Vector2 addVector2(Vector2 v1, Vector2 v2)
{
    Vector2 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

float calcDotProduct(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2 normaliseVector(Vector2 v)
{
    Vector2 nVec;
    float vecMag = sqrt(v.x * v.x + v.y * v.y);
    nVec.x = v.x / vecMag;
    nVec.y = v.y / vecMag;
    return nVec;
}