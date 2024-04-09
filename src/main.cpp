#include <raylib.h>

#include <cmath>
#include <memory>

#include "const.h"
#include "screens/landscape_screen.h"
#include "screens/screen.h"

constexpr auto kTargetFps = 60;

static std::unique_ptr<Screen> currentScreen = nullptr;
static RenderTexture2D target;

void UpdateDrawFrame() {
  auto newScreen = currentScreen->update();
  if (newScreen != currentScreen.get()) {
    currentScreen = std::unique_ptr<Screen>(newScreen);
  }

  float scale = fmin((float)GetScreenWidth() / kScreenWidth,
                     (float)GetScreenHeight() / kScreenHeight);
  BeginTextureMode(target);
  currentScreen->draw();
  DrawFPS(10, 10);
  EndTextureMode();
  BeginDrawing();
  ClearBackground(BLACK);

  // Draw render texture to screen, properly scaled
  DrawTexturePro(
      target.texture,
      {0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
      {(GetScreenWidth() - ((float)kScreenWidth * scale)) * 0.5f,
       (GetScreenHeight() - ((float)kScreenHeight * scale)) * 0.5f,
       (float)kScreenWidth * scale, (float)kScreenHeight * scale},
      {0, 0}, 0.0f, WHITE);
  EndDrawing();
}

int main(int argc, char const *argv[]) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(kScreenWidth, kScreenHeight, "Echo chamber");

  target = LoadRenderTexture(kScreenWidth, kScreenHeight);
  SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

  currentScreen = std::make_unique<LandscapeScreen>();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, kTargetFps, 1);
#else
  SetTargetFPS(kTargetFps);
  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();
  return 0;
}
