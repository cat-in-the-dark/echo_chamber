#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
  std::string name;

 public:
  Screen() = default;

  virtual ~Screen() = default;

  /// @brief Update curent screen
  /// @return New screen if state has changed
  virtual Screen *update() = 0;

  /// @brief Draw current screen
  virtual void draw() const = 0;
};

#endif /* SCREEN_H */
