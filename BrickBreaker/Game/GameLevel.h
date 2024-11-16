//
// GameLevel.h
// Author: Antoine Bastide
// Date: 15/11/2024
//

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include "Brick.h"

class GameLevel {
  public:
    // level state
    std::vector<Brick *> bricks;
    // constructor
    GameLevel(int index, int levelWidth, int levelHeight);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
};

#endif //GAMELEVEL_H
