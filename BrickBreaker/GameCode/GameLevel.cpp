//
// GameLevel.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <string>
#include <2D/ResourceManager.h>

#include "GameLevel.h"
#include "BrickBreaker.h"

std::vector<std::vector<std::vector<int> > > levels = {
  {
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4},
    {4, 1, 4, 1, 4, 0, 0, 1, 0, 0, 4, 1, 4, 1, 4},
    {3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3},
    {3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
  },
  {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 5, 5, 0, 1},
    {1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1},
    {1, 0, 3, 3, 0, 3, 3, 0, 3, 3, 0, 3, 3, 0, 1},
    {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
    {1, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0},
    {0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0},
    {0, 0, 5, 5, 0, 5, 5, 5, 0, 5, 5, 0, 0},
    {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
    {0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0},
    {0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 0},
    {0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0},
  },
  {
    {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 3, 1, 4, 1, 5, 1, 4, 1, 3, 1, 2},
    {2, 3, 3, 4, 4, 5, 5, 5, 4, 4, 3, 3, 2},
    {2, 1, 3, 1, 4, 1, 5, 1, 4, 1, 3, 1, 2},
    {2, 2, 3, 3, 4, 4, 5, 4, 4, 3, 3, 2, 2},
  }
};

GameLevel::GameLevel(const int index) {
  // Calculate dimensions
  const unsigned int width = levels[index][0].size();
  const unsigned int height = levels[index].size();
  const float unit_width = BrickBreaker::ViewportWidth() * 1.0f / width;
  const float unit_height = BrickBreaker::ViewportHeight() * 0.5f * 1.0f / height;

  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < width; x++) {
      // check block type from level data (2D level array)
      const Engine2D::Vector2 pos{
        -BrickBreaker::ViewportWidth() * 0.5f + unit_width * (0.5f + x),
        unit_height * (height - y - 0.5f)
      };
      const Engine2D::Vector2 size{unit_width, unit_height};
      if (levels[index][y][x] < 1)
        continue;

      std::string name = std::to_string(index) + ") Brick[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "]";
      BrickBreaker::AddEntity<Brick>(name);
      auto brick = BrickBreaker::Find<Brick>(name);
      brick->transform.position = pos;
      brick->transform.scale = size;
      brick->isSolid = levels[index][y][x] == 1;
      brick->lives = levels[index][y][x] == 1 ? 1 : levels[index][y][x] - 1;
      brick->SetTexture(Engine2D::ResourceManager::GetTexture(brick->isSolid ? "block_solid" : "block"));
      this->bricks.insert(brick);
    }
  }
}

bool GameLevel::IsCompleted() {
  return std::ranges::all_of(
    this->bricks, [](const std::shared_ptr<Brick> &tile) {
      return tile->isSolid;
    }
  );
}
