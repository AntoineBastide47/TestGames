//
// main.cpp
// Author: Antoine Bastide
// Date: 30/10/2024
//

#include <Engine2D/Game2D.hpp>
#include <cmrc/cmrc.hpp>
#include <string>

#include "BrickBreaker.hpp"

CMRC_DECLARE(resources);
CMRC_DECLARE(engine_resources);

int main() {
  BrickBreaker game{800, 600};
  game.SetGameResourceLoader(
    [](const std::string &path) {
      auto fs = cmrc::resources::get_filesystem();
      const std::string updated_path = path.starts_with("Game/") ? path : "Game/" + path;
      if (!fs.exists(updated_path)) {
        fs = cmrc::engine_resources::get_filesystem();
        if (!fs.exists(path))
          throw std::runtime_error("No such file or directory: " + path);
        return fs.open(path);
      }
      return fs.open(updated_path);
    }
  );
  game.Run();
}
