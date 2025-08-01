//
// SpaceInvaders.cpp
// Author: Antoine Bastide
// Date: 02/11/2024
//

#include <Engine/ResourceManager.hpp>
#include <Engine/Settings.hpp>
#include <Engine/Input/Keyboard.hpp>
#include <Engine2D/Entity2D.hpp>
#include <Engine2D/Rendering/SpriteRenderer.hpp>
#include <Engine2D/SceneManagement/SceneManager.hpp>

#include "BrickBreaker.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using Engine::ResourceManager;

BrickBreaker::BrickBreaker()
  : levelIndex(0) {}

BrickBreaker::BrickBreaker(const int width, const int height)
  : Game2D(width, height, "Brick Breaker"), levelIndex(0) {}

void Background::OnInitialize() {
  const auto renderer = Entity()->AddComponent<Engine2D::Rendering::SpriteRenderer>();
  renderer->SetSprite(ResourceManager::GetSprite("background"));
  Transform()->SetScale({BrickBreaker::ViewportWidth(), BrickBreaker::ViewportHeight()});
}

void BrickBreaker::OnInitialize() {
  Engine2D::SceneManager::CreateScene("SceneManager");
  Engine2D::SceneManager::SetActiveScene("SceneManager");

  // load textures
  ResourceManager::LoadTexture2D("atlas", "Assets/Textures/atlas.png");
  ResourceManager::CreateSprite("background", "atlas", {0.0f, 0.0f, 1.0f, 450.0f / 578.0f});
  ResourceManager::CreateSprite(
    "block", "atlas", {0.0f, 450.0f / 578.0f, 128.0f / 800.0f, 128.0f / 578.0f}
  )->transparent = false;
  ResourceManager::CreateSprite(
    "block_solid", "atlas", {128.0f / 800.0f, 450.0f / 578.0f, 128.0f / 800.0f, 128.0f / 578.0f}
  )->transparent = false;
  ResourceManager::CreateSprite(
    "paddle", "atlas", {256.0f / 800.0f, 450.0f / 578.0f, 512.0f / 800.0f, 128.0f / 578.0f}
  );
  ResourceManager::LoadTexture2DAndSprite("particle", "Assets/Textures/particle.png");
  ResourceManager::LoadTexture2DAndSprite("face", "Assets/Textures/awesomeface.png");

  // Disable friction so that the ball does not lose velocity
  Engine::Settings::Profiling::SetProfilingLevel(Engine::Settings::Profiling::ProfilingLevel::PerSystem);
  Engine::Settings::Profiling::SetProfilingThreshold(50);

  // Create all the entities
  Engine2D::Entity2D::Instantiate("background", true, {}, 0, glm::vec2{ViewportWidth(), ViewportHeight()})
      ->AddComponent<Background>();
  Engine2D::Entity2D::Instantiate("paddle")->AddComponent<Paddle>();
  Engine2D::Entity2D::Instantiate("ball")->AddComponent<Ball>();

  Reset();

  Engine::Input::Keyboard::ESCAPE += [this](const Engine::Input::KeyboardAndMouseContext ctx) {
    if (ctx.pressed)
      Quit();
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
