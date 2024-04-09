#include "render.h"

#include <raymath.h>
#include <rlgl.h>

#include "utils/collisions.h"

void DrawModelDots(Model model, Camera3D camera, Vector3 position, float scale,
                   Color tint) {
  auto mesh = model.meshes[0];
  auto vert = mesh.vertices;
  auto angleSize = 0.01f;

  raylib::Vector3 cameraPos{camera.position};
  raylib::Vector3 pos{position};

  for (int i = 0; i < mesh.triangleCount * 3; i += 3) {
    raylib::Vector3 centerPos =
        pos + raylib::Vector3{vert[3 * i], vert[3 * i + 1], vert[3 * i + 2]};
    DrawPoint3DConstSize(centerPos, cameraPos, angleSize, PointKind::PLUS,
                         tint);
  }
}

void DrawPoint3DConstSize(const raylib::Vector3 &pos,
                          const raylib::Vector3 &cameraPos, float angleSize,
                          PointKind kind, Color tint) {
  auto axis = cameraPos - pos;
  auto distance = axis.Length();
  auto angleTan = tanf(angleSize);
  auto size = distance * angleTan;

  switch (kind) {
    case PointKind::PLUS: {
      raylib::Vector3 vertical{0.0f, size / 2, 0.0f};
      auto horizontal =
          raylib::Vector3{Vector3RotateByAxisAngle(vertical, axis, PI / 2)};

      DrawLine3D(pos + vertical, pos - vertical, tint);
      DrawLine3D(pos + horizontal, pos - horizontal, tint);
      break;
    }
    case PointKind::CIRCLE: {
      // DrawCircle3D()
      break;
    }
    default: {
      break;
    }
  }
}

void DrawWaterLines(Mesh mesh, raylib::Vector3 pos, float waterLevel) {
  Plane waterPlane = {(Vector3){0, 1, 0}, waterLevel};

  for (int i = 0; i < mesh.triangleCount; i++) {
    raylib::Vector3 a, b, c;
    auto vertdata = reinterpret_cast<Vector3 *>(mesh.vertices);

    if (mesh.indices) {
      a = pos + vertdata[mesh.indices[i * 3 + 0]];
      b = pos + vertdata[mesh.indices[i * 3 + 1]];
      c = pos + vertdata[mesh.indices[i * 3 + 2]];
    } else {
      a = pos + vertdata[i * 3 + 0];
      b = pos + vertdata[i * 3 + 1];
      c = pos + vertdata[i * 3 + 2];
    }

    Triangle test = {a, b, c};
    Line3d out = {0};

    // printf("Check [%.2f;%.2f;%.2f][%.2f;%.2f;%.2f][%.2f;%.2f;%.2f] vs
    // %.2f\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, waterLevel);
    if (CheckCollisionTrianglePlane(test, waterPlane, &out)) {
      // printf("true: [%.2f;%.2f;%.2f][%.2f;%.2f;%.2f]\n", out.p1.x, out.p1.y,
      // out.p1.z, out.p2.x, out.p2.y, out.p2.z);
      DrawLine3D(out.p1, out.p2, BLUE);
    } else {
      // printf("false\n");
    }
  }
}
