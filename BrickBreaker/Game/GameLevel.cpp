//
// GameLevel.cpp
// Author: Antoine Bastide
// Date: 15/11/2024
//

#include "GameLevel.h"

#include <string>
#include <2D/ResourceManager.h>

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

GameLevel::GameLevel(const int index, const int levelWidth, const int levelHeight) {
  // Calculate dimensions
  const unsigned int width = levels[index][0].size();
  const unsigned int height = levels[index].size();
  const float unit_width = levelWidth * 1.0f / width;
  const float unit_height = levelHeight * 1.0f / height;

  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < width; x++) {
      // check block type from level data (2D level array)
      const glm::vec2 pos(unit_width * x, unit_height * y);
      const glm::vec2 size(unit_width, unit_height);
      if (levels[index][y][x] == 1) {
        auto brick = new Brick(
                               "Brick[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "]",
                               nullptr,
                               Engine2D::ResourceManager::GetTexture("block_solid"),
                               true
                              );
        brick->transform.position = pos;
        brick->transform.scale = size;
        brick->textureColor = new glm::vec3(0.8f, 0.8f, 0.7f);
        this->bricks.push_back(brick);
      }
      else if (levels[index][y][x] > 1) {
        auto brick = new Brick(
                               "Brick[" + std::to_string(pos.x) + "][" + std::to_string(pos.y) + "]",
                               nullptr,
                               Engine2D::ResourceManager::GetTexture("block"),
                               false
                              );
        if (levels[index][y][x] == 2)
          brick->textureColor = new glm::vec3(0.2f, 0.6f, 1.0f);
        else if (levels[index][y][x] == 3)
          brick->textureColor = new glm::vec3(0.0f, 0.7f, 0.0f);
        else if (levels[index][y][x] == 4)
          brick->textureColor = new glm::vec3(0.8f, 0.8f, 0.4f);
        else if (levels[index][y][x] == 5)
          brick->textureColor = new glm::vec3(1.0f, 0.5f, 0.0f);

        brick->transform.position = pos;
        brick->transform.scale = size;
        this->bricks.push_back(brick);
      }
    }
  }
}

bool GameLevel::IsCompleted() {
  return std::ranges::all_of(this->bricks, [](const Brick *tile) { return tile->isSolid || tile->destroyed; });
}
