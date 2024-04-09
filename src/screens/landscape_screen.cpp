#include "landscape_screen.h"

#include <iostream>

#include "const.h"
#include "utils/perlin.h"
#include "utils/render.h"

LandscapeScreen::LandscapeScreen()
    : camera_{{18.0f, 18.0f, 18.0f},
              {0.0f, 0.0f, 0.0f},
              {0.0f, 1.0f, 0.0f},
              45.0f,
              0},
      mapPosition_{-8.0f, 0.0f, -8.0f},
      waterLevel_{2},
      Screen() {
  std::cout << "Landscape init" << std::endl;

  auto image = GenImagePerlin(128, 128);
  landscapeTexture_ = LoadTextureFromImage(image);
  auto mesh = GenMeshHeightmap(image, {16, 8, 16});

  landscape_ = LoadModelFromMesh(mesh);

  landscape_.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      landscapeTexture_;

  UnloadImage(image);
}

LandscapeScreen::~LandscapeScreen() {
  std::cout << "Landscape ends" << std::endl;
  UnloadTexture(landscapeTexture_);
  UnloadModel(landscape_);
}

Screen *LandscapeScreen::update() {
  waterLevel_ += 0.005;
  UpdateCamera(&camera_, CAMERA_ORBITAL);
  return this;
}

void LandscapeScreen::draw() const {
  ClearBackground(RAYWHITE);

  Color color = RED;

  BeginMode3D(camera_);
  DrawModelDots(landscape_, camera_, mapPosition_, 1.0f, color);
  DrawWaterLines(landscape_.meshes[0], mapPosition_, waterLevel_);

  DrawGrid(20, 1.0f);
  EndMode3D();

  DrawTexture(landscapeTexture_, kScreenWidth - landscapeTexture_.width - 20,
              20, WHITE);
  DrawRectangleLines(kScreenWidth - landscapeTexture_.width - 20, 20,
                     landscapeTexture_.width, landscapeTexture_.height, GREEN);
}
