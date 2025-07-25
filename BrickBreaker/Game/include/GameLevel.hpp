//
// GameLevel.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include "Brick.hpp"

class GameLevel {
  public:
    Engine2D::Entity2D *level;
    // level state
    std::vector<Brick *> bricks;
    // constructor
    explicit GameLevel(int index);
};

#endif //GAME_LEVEL_H
