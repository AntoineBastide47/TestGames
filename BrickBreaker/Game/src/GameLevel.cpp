//
// GameLevel.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include <string>
#include <Engine2D/ResourceManager.hpp>

#include "GameLevel.hpp"
#include "BrickBreaker.hpp"

std::vector<std::vector<std::vector<int>>> levels = {
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
  level = BrickBreaker::AddEntity("level" + std::to_string(index));

  // Calculate dimensions
  const unsigned int width = levels[index][0].size();
  const unsigned int height = levels[index].size();
  const float unit_width = BrickBreaker::ViewportWidth() * 1.0f / width;
  const float unit_height = BrickBreaker::ViewportHeight() * 0.5f * 1.0f / height;

  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < width; x++) {
      if (levels[index][y][x] < 1)
        continue;

      const glm::vec2 size{unit_width, unit_height};
      const glm::vec2 pos = size * glm::vec2(x - width * 0.5f + 0.5f, height - y - 0.5f);

      auto brick = BrickBreaker::AddEntity(
        "Brick[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "]"
      )->AddComponent<Brick>();
      brick->Transform()->SetPositionRotationAndScale(pos, 0, size);
      brick->isSolid = levels[index][y][x] == 1;
      brick->lives = levels[index][y][x] == 1 ? 1 : levels[index][y][x] - 1;
      brick->Entity()->SetTexture(Engine2D::ResourceManager::GetTexture(brick->isSolid ? "block_solid" : "block"));
      brick->Entity()->textureColor = Brick::GetColor(brick->isSolid, brick->lives);
      brick->Transform()->SetParent(level);
      bricks.emplace_back(brick);
    }
  }
}