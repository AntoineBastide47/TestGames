//
// GameLevel.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include "Brick.h"

class GameLevel {
  public:
    // level state
    std::vector<Brick *> bricks;
    // constructor
    explicit GameLevel(int index);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
};

#endif //GAME_LEVEL_H
