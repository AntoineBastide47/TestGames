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

class BrickBreaker final : public Engine2D::Game2D {
  public:
    static std::vector<GameLevel> levels;
    static int levelIndex;
    Engine2D::Entity2D background;
    static Paddle *paddle;
    static Ball *ball;

    BrickBreaker(int width, int height);
    ~BrickBreaker() override;

    void Initialize() override;
    static void ChangeLevel(int newLevel);
    static void Reset();
};

#endif //BRICK_BREAKER_H
