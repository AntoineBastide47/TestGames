//
// main.cpp
// Author: Antoine Bastide
// Date: 30/10/2024
//

#include <iostream>

#include "2D/Game2D.h"

#include "Game/BrickBreaker.h"
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(resources);
CMRC_DECLARE(engine_resources);

int main() {
  BrickBreaker game{800, 600};
  game.SetGameResourceLoader([](const std::string& path) {
    auto fs = cmrc::resources::get_filesystem();
    if (!fs.exists(path)) {
      fs = cmrc::engine_resources::get_filesystem();
      if (!fs.exists(path))
        throw std::runtime_error("No such file or directory: " + path);
    }
    return fs.open(path);
  });
  game.Run();
  return 0;
}
