//
// SpaceInvaders.h
// Author: Antoine Bastide
// Date: 02/11/2024
//

#ifndef BRICK_BREAKER_H
#define BRICK_BREAKER_H

#include <2D/Game2D.h>

#include "Ball.h"
#include "GameLevel.h"
#include "Paddle.h"

class Background : public Engine2D::Entity2D {
  public:
    explicit Background(const std::string &name) : Entity2D(name) {}
    void Initialize() override;
};

class BrickBreaker final : public Engine2D::Game2D {
  public:
    static std::unordered_map<int, GameLevel> levels;
    static int levelIndex;

    static std::shared_ptr<Paddle> paddle;
    static std::shared_ptr<Ball> ball;
    static std::shared_ptr<Background> background;

    BrickBreaker(int width, int height);

    void Initialize() override;
    static void ChangeLevel(int newLevel);
    static void Reset();
};

#endif //BRICK_BREAKER_H
