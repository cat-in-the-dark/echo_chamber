#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <raylib.h>

#include "utils/types.h"

bool CheckCollisionTrianglePlane(Triangle triangle, Plane plane,
                                 Line3d* outLine);

bool CheckCollisionBoxTriangle(BoundingBox box, Triangle triangle);

TriangleCollisionInfo CheckCollisionBoxMesh(BoundingBox box, Mesh mesh,
                                            Matrix transform);

bool CheckCollisionLineRec(Vector2 startPos, Vector2 endPos, Rectangle rec);

#endif /* COLLISIONS_H */
