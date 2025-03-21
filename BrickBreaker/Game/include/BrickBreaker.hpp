//
// SpaceInvaders.h
// Author: Antoine Bastide
// Date: 02/11/2024
//

#ifndef BRICK_BREAKER_H
#define BRICK_BREAKER_H

#include <Engine2D/Game2D.hpp>
#include <Engine2D/Behaviour.hpp>

#include "GameLevel.hpp"

class Background : public Engine2D::Behaviour {
  public:
    void OnInitialize() override;
};

class BrickBreaker final : public Engine2D::Game2D {
  public:
    std::vector<GameLevel> levels;
    int levelIndex;

    BrickBreaker(int width, int height);

    void OnInitialize() override;
    void ChangeLevel(int newLevel);
    void Reset();
};

#endif //BRICK_BREAKER_H
