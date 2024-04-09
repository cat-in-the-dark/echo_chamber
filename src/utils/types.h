#ifndef TYPES_H
#define TYPES_H

#include <raylib.h>

struct Triangle {
  Vector3 p1;
  Vector3 p2;
  Vector3 p3;
};

struct Line3d {
  union {
    struct {
      Vector3 p1;
      Vector3 p2;
    };
    Vector3 coords[2];
  };
};

struct Plane {
  Vector3 norm;
  float dist;
};

struct TriangleCollisionInfo {
  bool hit;
  Triangle triangle;
};

#endif /* TYPES_H */
