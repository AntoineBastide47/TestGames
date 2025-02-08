//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include <Engine2D/Entity2D.h>
#include <Engine2D/ResourceManager.h>
#include <Common/Settings.h>
#include <Input/Keyboard.h>

#include "BrickBreaker.h"
#include "Ball.h"
#include "Paddle.h"

using Engine2D::ResourceManager;

std::unordered_map<int, GameLevel> BrickBreaker::levels{};
int BrickBreaker::levelIndex = 0;

void Background::OnInitialize() {
  SetTexture(ResourceManager::GetTexture("background"));
  transform.SetScale({BrickBreaker::ViewportWidth(), BrickBreaker::ViewportHeight()});
}

BrickBreaker::BrickBreaker(const int width, const int height) : Game2D(width, height, "Brick Breaker") {}

void BrickBreaker::OnInitialize() {
  // load textures
  ResourceManager::LoadTexture("Assets/Textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("Assets/Textures/block.png", false, "block");
  ResourceManager::LoadTexture("Assets/Textures/block_solid.png", false, "block_solid");
  ResourceManager::LoadTexture("Assets/Textures/paddle.png", true, "paddle");
  ResourceManager::LoadTexture("Assets/Textures/awesomeface.png", true, "face");
  ResourceManager::LoadTexture("Assets/Textures/particle.png", true, "particle");

  // Disable friction so that the ball does not lose velocity
  Engine::Settings::Physics::SetFrictionEnabled(false);

  // Create all the entities
  AddEntity<Background>("background");
  AddEntity<Paddle>("paddle");
  AddEntity<Ball>("ball");

  // Load the game levels
  /*
  */
  levels.emplace(0, GameLevel(0));
  levels.emplace(1, GameLevel(1));
  levels.emplace(2, GameLevel(2));
  levels.emplace(3, GameLevel(3));

  ChangeLevel(0);

  Engine::Input::Keyboard::ESCAPE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    Close(ctx);
  };

  // Remove frame rate cap to test performance changes
  Engine::Input::Keyboard::T += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed)
      Engine::Settings::Graphics::SetVsyncEnabled(!Engine::Settings::Graphics::GetVsyncEnabled());
  };
}

void BrickBreaker::ChangeLevel(const int newLevel) {
  for (auto &[levelIndex, level]: levels)
    for (const auto &brick: level.bricks)
      brick->SetActive(levelIndex == newLevel);
  levelIndex = newLevel;
}

void BrickBreaker::Reset() {
  // Create all the entities
  //paddle->transform.position = Engine2D::Vector2{0, (paddle->transform.scale.y - Height()) * 0.5f};
  //ball->transform.SetParent(paddle);
  //ball->transform.position = Engine2D::Vector2{0, 1.5f};

  // Load the game levels
  levels.emplace(0, GameLevel(0));
  levels.emplace(1, GameLevel(1));
  levels.emplace(2, GameLevel(2));
  levels.emplace(3, GameLevel(3));

  // Load level 0 and unload all the others
  ChangeLevel(0);
}
