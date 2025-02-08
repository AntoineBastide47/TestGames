//
// SpaceInvaders.h
// Author: Antoine Bastide
// Date: 02/11/2024
//

#ifndef BRICK_BREAKER_H
#define BRICK_BREAKER_H

#include <unordered_map>
#include <Engine2D/Game2D.h>

#include "GameLevel.h"

class Background : public Engine2D::Entity2D {
  public:
    explicit Background(const std::string &name) : Entity2D(name) {}
    void OnInitialize() override;
};

class BrickBreaker final : public Engine2D::Game2D {
  public:
    static std::unordered_map<int, GameLevel> levels;
    static int levelIndex;

    BrickBreaker(int width, int height);

    void OnInitialize() override;
    static void ChangeLevel(int newLevel);
    static void Reset();
};

#endif //BRICK_BREAKER_H
