#include "seanMath.h"

Vector2 addVector2(Vector2 v1, Vector2 v2)
{
    Vector2 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

Vector3 addVector3(Vector3 v1, Vector3 v2)
{
    Vector3 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}