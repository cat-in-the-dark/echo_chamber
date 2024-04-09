#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>

#include "Vector3.hpp"

enum class PointKind { PLUS, CIRCLE };

void DrawPoint3DConstSize(const raylib::Vector3 &pos,
                          const raylib::Vector3 &cameraPos, float angleSize,
                          PointKind kind, Color tint);

void DrawModelDots(Model model, Camera3D camera, Vector3 position, float scale,
                   Color tint);

void DrawWaterLines(Mesh mesh, raylib::Vector3 pos, float waterLevel);

#endif /* RENDER_H */
