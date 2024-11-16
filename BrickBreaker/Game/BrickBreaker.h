//
// SpaceInvaders.h
// Author: Antoine Bastide
// Date: 02/11/2024
//

#ifndef BRICKBREAKER_H
#define BRICKBREAKER_H

#include "GameLevel.h"
#include "Player.h"
#include "2D/Game2D.h"

enum GameState {
  GAME_ACTIVE, GAME_MENU, GAME_WIN
};

class BrickBreaker final : public Engine2D::Game2D {
  public:
    std::vector<GameLevel> levels;
    int levelIndex;
    Engine2D::Entity2D *background;
    Player *player;
    float timer = 0.0f;

    BrickBreaker(int16 width, int16 height);

    void Initialize() override;
    void ChangeLevel(int newLevel);
};

#endif //BRICKBREAKER_H
