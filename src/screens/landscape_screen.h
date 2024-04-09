#ifndef LANDSCAPE_SCREEN_H
#define LANDSCAPE_SCREEN_H

#include <raylib.h>

#include "screen.h"

class LandscapeScreen : public Screen {
 public:
  LandscapeScreen();
  ~LandscapeScreen();
  virtual Screen *update() override;
  virtual void draw() const override;

 private:
  Camera camera_;
  Model landscape_;
  Texture landscapeTexture_;
  Vector3 mapPosition_;
  float waterLevel_;
};

#endif /* LANDSCAPE_SCREEN_H */
