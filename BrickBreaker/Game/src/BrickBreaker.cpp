//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include <Engine2D/Entity2D.hpp>
#include <Engine2D/ResourceManager.hpp>
#include <Engine/Settings.hpp>
#include <Engine/Input/Keyboard.hpp>
#include <Engine/Macros/Assert.hpp>

#include "BrickBreaker.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using Engine2D::ResourceManager;

BrickBreaker::BrickBreaker(const int width, const int height) : Game2D(width, height, "Brick Breaker"), levelIndex(0) {}

void Background::OnInitialize() {
  Entity()->SetTexture(ResourceManager::GetTexture("background"));
  Transform()->SetScale({BrickBreaker::ViewportWidth(), BrickBreaker::ViewportHeight()});
}

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
  AddEntity("background")->AddComponent<Background>();
  AddEntity("paddle")->AddComponent<Paddle>();
  AddEntity("ball")->AddComponent<Ball>();

  Reset();

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
  for (int i = 0; i < levels.size(); ++i)
    levels[i].level->SetActive(i == newLevel);
  levelIndex = newLevel;
}

void BrickBreaker::Reset() {
  levels = {
    GameLevel(0),
    GameLevel(1),
    GameLevel(2),
    GameLevel(3),
  };

  ChangeLevel(0);
}
