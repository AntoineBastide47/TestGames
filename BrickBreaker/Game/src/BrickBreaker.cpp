//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include <Engine2D/Entity2D.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/Settings.hpp>
#include <Engine/Input/Keyboard.hpp>
#include <Engine2D/Rendering/SpriteRenderer.hpp>

#include "BrickBreaker.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using Engine::ResourceManager;

BrickBreaker::BrickBreaker(const int width, const int height) : Game2D(width, height, "Brick Breaker"), levelIndex(0) {}

void Background::OnInitialize() {
  const auto renderer = Entity()->AddComponent<Engine2D::Rendering::SpriteRenderer>();
  renderer->SetSprite(ResourceManager::GetSprite("background"));
  Transform()->SetScale({BrickBreaker::ViewportWidth(), BrickBreaker::ViewportHeight()});
}

void BrickBreaker::OnInitialize() {
  // load textures
  ResourceManager::LoadTexture2D("Assets/Textures/atlas.png", "atlas");
  ResourceManager::CreateSprite("background", "atlas", false, {0.0f, 0.0f, 1.0f, 450.0f / 578.0f});
  ResourceManager::CreateSprite("block", "atlas", false, {0.0f, 450.0f / 578.0f, 128.0f / 800.0f, 128.0f / 578.0f});
  ResourceManager::CreateSprite(
    "block_solid", "atlas", false, {128.0f / 800.0f, 450.0f / 578.0f, 128.0f / 800.0f, 128.0f / 578.0f}
  );
  ResourceManager::CreateSprite(
    "paddle", "atlas", true, {256.0f / 800.0f, 450.0f / 578.0f, 512.0f / 800.0f, 128.0f / 578.0f}
  );
  ResourceManager::LoadTexture2DAndSprite("Assets/Textures/particle.png", "particle", true);
  ResourceManager::LoadTexture2DAndSprite("Assets/Textures/awesomeface.png", "face", true);

  // Disable friction so that the ball does not lose velocity
  Engine::Settings::Physics::SetFrictionEnabled(false);
  Engine::Settings::Profiling::SetProfilingLevel(Engine::Settings::Profiling::ProfilingLevel::PerSystem);

  // Create all the entities
  AddEntity("background", true, {}, 0, {ViewportWidth(), ViewportHeight()})->AddComponent<Background>();
  AddEntity("paddle")->AddComponent<Paddle>();
  AddEntity("ball")->AddComponent<Ball>();

  Reset();

  Engine::Input::Keyboard::ESCAPE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    Close(ctx);
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
