#include "perlin.h"

#include <math.h>
#include <stdio.h>

#include "const.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"
#include "utils/collisions.h"

#define W SCREEN_WIDTH - 40
#define H SCREEN_HEIGHT - 60
#define CELL_SIZE 32.0f

#define GRID_SIZE 128

typedef struct {
  bool occupied;
  Vector2 coords;
} GradientCell;

GradientCell gradients[GRID_SIZE][GRID_SIZE];

Vector2 randomGradient(int ix, int iy) {
  if (!gradients[ix][iy].occupied) {
    float angle = Remap(GetRandomValue(0, 1000), 0, 1000, 0.0, PI * 2);
    gradients[ix][iy].coords.x = cosf(angle);
    gradients[ix][iy].coords.y = sinf(angle);
    gradients[ix][iy].occupied = true;
  }

  return gradients[ix][iy].coords;
}

// /* Create pseudorandom direction vector
//  */
// Vector2 randomGradient(int ix, int iy) {
//     // No precomputed gradients mean this works for any number of grid
//     coordinates const unsigned w = 8 * sizeof(unsigned); const unsigned s = w
//     / 2; // rotation width unsigned a = ix, b = iy; a *= 3284157443; b ^= a
//     << s | a >> w-s; b *= 1911520717; a ^= b << s | b >> w-s; a *=
//     2048419325; float random = a * (3.14159265 / ~(~0u >> 1)); // in [0,
//     2*Pi] Vector2 v; v.x = cosf(random); v.y = sinf(random); return v;
// }

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {
  // Get gradient from integer coordinates
  Vector2 gradient = randomGradient(ix, iy);

  // Compute the distance vector
  Vector2 dist = {x - (float)ix, y - (float)iy};

  return Vector2DotProduct(dist, gradient);
}

float interpolate(float a0, float a1, float w) {
  // cubic interpolation
  return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y) {
  // Determine grid cell coordinates
  int x0 = (int)floor(x);
  int x1 = x0 + 1;
  int y0 = (int)floor(y);
  int y1 = y0 + 1;

  // Determine interpolation weights
  // Could also use higher order polynomial/s-curve here
  float sx = x - (float)x0;
  float sy = y - (float)y0;

  // Interpolate between grid point gradients
  float n0, n1, ix0, ix1, value;

  n0 = dotGridGradient(x0, y0, x, y);
  n1 = dotGridGradient(x1, y0, x, y);
  ix0 = interpolate(n0, n1, sx);

  n0 = dotGridGradient(x0, y1, x, y);
  n1 = dotGridGradient(x1, y1, x, y);
  ix1 = interpolate(n0, n1, sx);

  value = interpolate(ix0, ix1, sy);
  // [-0.5; 0.5] => [0.0; 1.0]
  return (value + 0.5f);
}

Image GenImagePerlin(int width, int height) {
  Image image = GenImageColor(width, height, RAYWHITE);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      float noise = (perlin(i / CELL_SIZE, j / CELL_SIZE) +
                     0.5 * perlin(i / CELL_SIZE * 2, j / CELL_SIZE * 2) +
                     0.25 * perlin(i / CELL_SIZE * 4, j / CELL_SIZE * 4)) /
                    1.75;
      // [0.0; 1.0] => [0; 255]
      unsigned char value = (unsigned char)(noise * 255);
      Color color = {value, value, value, 255};
      ImageDrawPixel(&image, i, j, color);
    }
  }

  return image;
}
