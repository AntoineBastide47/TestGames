//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include <iostream>
#include <2D/Entity2D.h>
#include <2D/ResourceManager.h>
#include <Input/Keyboard.h>
#include <Common/Macros.h>

#include "BrickBreaker.h"

using Engine2D::ResourceManager;

Paddle *BrickBreaker::paddle{};
Ball *BrickBreaker::ball{};
std::vector<GameLevel> BrickBreaker::levels{};
int BrickBreaker::levelIndex = 0;

BrickBreaker::BrickBreaker(const int width, const int height)
  : Game2D(width, height, "Brick Breaker"), background("background") {}

BrickBreaker::~BrickBreaker() {
  SAFE_DELETE(paddle);
  SAFE_DELETE(ball);
}

void BrickBreaker::Initialize() {
  // load textures
  ResourceManager::LoadTexture("Assets/Textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("Assets/Textures/block.png", false, "block");
  ResourceManager::LoadTexture("Assets/Textures/block_solid.png", false, "block_solid");
  ResourceManager::LoadTexture("Assets/Textures/paddle.png", true, "paddle");
  ResourceManager::LoadTexture("Assets/Textures/awesomeface.png", true, "face");

  // Create all the entities
  background.texture = ResourceManager::GetTexture("background");
  background.transform.scale = Engine2D::Vector2(ViewportWidth(), ViewportHeight());
  paddle = new Paddle("paddle", nullptr, ResourceManager::GetTexture("paddle"));

  // Load the game levels
  levels.emplace_back(0);
  levels.emplace_back(1);
  levels.emplace_back(2);
  levels.emplace_back(3);

  // Load level 0 and unload all the others
  ChangeLevel(0);
  ball = new Ball("ball", ResourceManager::GetTexture("face"));

  Engine::Input::Keyboard::ESCAPE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    Close(ctx);
  };
}

void BrickBreaker::ChangeLevel(const int newLevel) {
  for (int i = 0; i < levels.size(); ++i)
    for (const auto brick: levels[i].bricks)
      brick->active = i == newLevel;
  levelIndex = newLevel;
}

void BrickBreaker::Reset() {
  // Create all the entities
  //paddle->transform.position = Engine2D::Vector2{0, (paddle->transform.scale.y - Height()) * 0.5f};
  //ball->transform.SetParent(paddle);
  //ball->transform.position = Engine2D::Vector2{0, 1.5f};

  // Load the game levels
  levels.emplace_back(0);
  levels.emplace_back(1);
  levels.emplace_back(2);
  levels.emplace_back(3);

  // Load level 0 and unload all the others
  ChangeLevel(0);
}
